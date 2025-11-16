#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sched.h>
#include <string.h>
#include <time.h>
#include <errno.h>

typedef struct {
    char *name;
    int policy;
    int priority;
    long long duration_ms;
} TaskParams;

void print_usage(const char *program_name) {
    printf("Usage: %s --name <name> --policy <policy> --priority <value> --time <ms>\n", program_name);
    printf("\nOptions:\n");
    printf("  -t, --name <name>     Job name (required)\n");
    printf("  -p, --policy <policy> Scheduling policy (other, fifo, rr)\n");
    printf("  -r, --priority <val>  Priority value\n");
    printf("  -m, --time <ms>       Run time in milliseconds (required)\n");
    printf("  -h, --help            Display this help message\n");
}

int parse_policy(const char *policy_str) {
    if (strcasecmp(policy_str, "other") == 0) return SCHED_OTHER;
    if (strcasecmp(policy_str, "fifo") == 0)  return SCHED_FIFO;
    if (strcasecmp(policy_str, "rr") == 0)    return SCHED_RR;
    return -1;
}

const char *policy_to_string(int policy) {
    switch (policy) {
        case SCHED_OTHER: return "SCHED_OTHER";
        case SCHED_FIFO:  return "SCHED_FIFO";
        case SCHED_RR:    return "SCHED_RR";
        default:          return "UNKNOWN";
    }
}

int parse_arguments(int argc, char *argv[], TaskParams *params) {
    // Default values
    params->name = NULL;
    params->policy = SCHED_OTHER;
    params->priority = 0;
    params->duration_ms = -1;

    static struct option long_options[] = {
        {"name", required_argument, 0, 't'},
        {"policy", required_argument, 0, 'p'},
        {"priority", required_argument, 0, 'r'},
        {"time", required_argument, 0, 'm'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    int opt;
    int option_index = 0;
    
    while ((opt = getopt_long(argc, argv, "t:p:r:m:h", long_options, &option_index)) != -1) {
        switch (opt) {
            case 't':
                params->name = optarg;
                if (!params->name) {
                    fprintf(stderr, "Error: --name is required\n");
                    return 0;
                }
                break;

            case 'p': 
                int policy = parse_policy(optarg);
                if (policy == -1) {
                    fprintf(stderr, "Error: Invalid policy '%s'. Valid options: other, fifo, rr\n", optarg);
                    return 0;
                }
                params->policy = policy;
                break;

            case 'r':
                params->priority = atoi(optarg);
                break;

            case 'm':
                params->duration_ms = atoll(optarg);
                if (params->duration_ms <= 0) {
                    fprintf(stderr, "Error: --time must be > 0\n");
                    return 0;
                }
                break;

            case 'h':
                print_usage(argv[0]);
                exit(EXIT_SUCCESS);

            default:
                return 0;
        }
    }

    return 1;
}

long long current_time_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000LL) + (ts.tv_nsec / 1000000LL);
}

int main(int argc, char **argv) {
    TaskParams params = {0};  

    if (argc < 2) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_arguments(argc, argv, &params)) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    // Set scheduler
    struct sched_param param;
    param.sched_priority = params.priority;
    if (sched_setscheduler(0, params.policy, &param) == -1) {
        fprintf(stderr, "Warning: sched_setscheduler failed: %s\n", strerror(errno));
    }

    long long start_time = current_time_ms();
    long long now = start_time;
    long long end_time = start_time + params.duration_ms;

    long long n = 0;

    printf("Job '%s' started (policy=%s, priority=%d)\n",
           params.name,
           policy_to_string(params.policy),
           params.priority);

    while (now < end_time) {
        n++;
        if (!(n % 10000000)) {
            int current_cpu = sched_getcpu();
            printf("Job '%s': (CPU %d, %s, prio=%d) n=%llu\n",
                   params.name,
                   current_cpu,
                   policy_to_string(params.policy),
                   params.priority,
                   n);
            fflush(stdout);
        }
        now = current_time_ms();
    }

    printf("Job '%s' completed after %lld ms\n", params.name, params.duration_ms);
    return 0;
}
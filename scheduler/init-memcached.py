from pymemcache.client import base

dbschedule = {

    #<nametable>:<attribute> = value
    "schedule:version":"1",
    "schedule:length":"18",

    #<nametable>:<key> = value
    "scheduletask:1": '{nametask:"INIT_CORE", starttime:"0", endtime:"14", repetition:"R1", priority:"135"}',
    "scheduletask:2": '{nametask:"COMM_PROTO", starttime:"0", endtime:"16", repetition:"R1", priority:"136"}',
    "scheduletask:3": '{nametask:"CTRL_EXEC", starttime:"2", endtime:"5", repetition:"R1", priority:"133"}',
    "scheduletask:4": '{nametask:"CTRL_EXEC", starttime:"10", endtime:"13", repetition:"R2", priority:"133"}',
    "scheduletask:5": '{nametask:"CTRL_EXEC", starttime:"18", endtime:"21", repetition:"R3", priority:"133"}',
    "scheduletask:6": '{nametask:"CTRL_EXEC", starttime:"26", endtime:"29", repetition:"R4", priority:"133"}',
    "scheduletask:7": '{nametask:"SYNC_PROC", starttime:"4", endtime:"6", repetition:"R1", priority:"134"}',
    "scheduletask:8": '{nametask:"SYNC_PROC", starttime:"12", endtime:"14", repetition:"R2", priority:"134"}',
    "scheduletask:9": '{nametask:"SYNC_PROC", starttime:"20", endtime:"22", repetition:"R3", priority:"134"}',
    "scheduletask:10": '{nametask:"SYNC_PROC", starttime:"28", endtime:"30", repetition:"R4", priority:"134"}',
    "scheduletask:11": '{nametask:"ANALYSIS_FULL", starttime:"4", endtime:"18", repetition:"R1", priority:"137"}',
    "scheduletask:12": '{nametask:"VERIFY_QUICK", starttime:"12", endtime:"19", repetition:"R1", priority:"138"}',
    "scheduletask:13": '{nametask:"PREPROCESS_SVC", starttime:"18", endtime:"31", repetition:"R1", priority:"140"}',
    "scheduletask:14": '{nametask:"POSTPROCESS_SVC", starttime:"20", endtime:"32", repetition:"R1", priority:"142"}',
    "scheduletask:15": '{nametask:"ORBIT_CTRL", starttime:"18", endtime:"31", repetition:"R1", priority:"141"}',
    "scheduletask:16": '{nametask:"ORBIT_MGMT", starttime:"18", endtime:"32", repetition:"R1", priority:"206"}',
    "scheduletask:17": '{nametask:"MONITOR_SYS", starttime:"10", endtime:"22", repetition:"R1", priority:"210"}',
    "scheduletask:18": '{nametask:"SAFE_DIR", starttime:"0", endtime:"12", repetition:"R1", priority:"139"}'

}

# Connect to memcached
client = base.Client(('127.0.0.1', 11211))

# Init memcached 
client.set("schedule:version","1")
client.set("schedule:length", "1")

client.set("scheduletask:1", '{nametask:"INIT_CORE", starttime:"0", endtime:"14", repetition:"R1", priority:"135"}')
client.set("scheduletask:2", '{nametask:"COMM_PROTO", starttime:"0", endtime:"16", repetition:"R1", priority:"136"}')
client.set("scheduletask:3", '{nametask:"CTRL_EXEC", starttime:"2", endtime:"5", repetition:"R1", priority:"133"}')
client.set("scheduletask:4", '{nametask:"CTRL_EXEC", starttime:"10", endtime:"13", repetition:"R2", priority:"133"}')
client.set("scheduletask:5", '{nametask:"CTRL_EXEC", starttime:"18", endtime:"21", repetition:"R3", priority:"133"}')
client.set("scheduletask:6", '{nametask:"CTRL_EXEC", starttime:"26", endtime:"29", repetition:"R4", priority:"133"}')
client.set("scheduletask:7", '{nametask:"SYNC_PROC", starttime:"4", endtime:"6", repetition:"R1", priority:"134"}')
client.set("scheduletask:8", '{nametask:"SYNC_PROC", starttime:"12", endtime:"14", repetition:"R2", priority:"134"}')
client.set("scheduletask:9", '{nametask:"SYNC_PROC", starttime:"20", endtime:"22", repetition:"R3", priority:"134"}')
client.set("scheduletask:10", '{nametask:"SYNC_PROC", starttime:"28", endtime:"30", repetition:"R4", priority:"134"}')
client.set("scheduletask:11", '{nametask:"ANALYSIS_FULL", starttime:"4", endtime:"18", repetition:"R1", priority:"137"}')
client.set("scheduletask:12", '{nametask:"VERIFY_QUICK", starttime:"12", endtime:"19", repetition:"R1", priority:"138"}')
client.set("scheduletask:13", '{nametask:"PREPROCESS_SVC", starttime:"18", endtime:"31", repetition:"R1", priority:"140"}')
client.set("scheduletask:14", '{nametask:"POSTPROCESS_SVC", starttime:"20", endtime:"32", repetition:"R1", priority:"142"}')
client.set("scheduletask:15", '{nametask:"ORBIT_CTRL", starttime:"18", endtime:"31", repetition:"R1", priority:"141"}')
client.set("scheduletask:16", '{nametask:"ORBIT_MGMT", starttime:"18", endtime:"32", repetition:"R1", priority:"206"}')
client.set("scheduletask:17", '{nametask:"MONITOR_SYS", starttime:"10", endtime:"22", repetition:"R1", priority:"210"}')
client.set("scheduletask:18", '{nametask:"SAFE_DIR", starttime:"0", endtime:"12", repetition:"R1", priority:"139"}')




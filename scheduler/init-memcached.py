from pymemcache.client import base

dbschedule = {

    #<nametable>:<attribute> = value
    "schedule:version":"1",
    "schedule:length":"1",

    #<nametable>:<key>:<attribute> = value
    "scheduletask:1:nametask":"INIT_CORE",
    "scheudletask:1:starttime":"0",
    "scheduletask:1:endtime":"14",
    "scheduletask:1:repetition":"R1",
    "scheduletask:1:priority":"135"

}

# Connect to memcached
client = base.Client(('127.0.0.1', 11211))

# Init memcached 
client.set("schedule:version","1")
client.set("schedule:length", "1")

client.set("scheduletask:1:nametask","INIT_CORE")
client.set("scheudletask:1:starttime","0")
client.set("scheduletask:1:endtime","14")
client.set("scheduletask:1:repetition","R1")
client.set("scheduletask:1:priority","135")



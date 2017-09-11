            if (!strcasecmp(c->argv[j]->ptr,"crash-after-election")) {
                sentinel.simfailure_flags |=
                    SENTINEL_SIMFAILURE_CRASH_AFTER_ELECTION;
                redisLog(REDIS_WARNING,"Failure simulation: this Sentinel "
                    "will crash after being successfully elected as failover "
                    "leader");
            } else if (!strcasecmp(c->argv[j]->ptr,"crash-after-promotion")) {
                sentinel.simfailure_flags |=
                    SENTINEL_SIMFAILURE_CRASH_AFTER_PROMOTION;
                redisLog(REDIS_WARNING,"Failure simulation: this Sentinel "
                    "will crash after promoting the selected slave to master");
            } else if (!strcasecmp(c->argv[j]->ptr,"help")) {
                addReplyMultiBulkLen(c,2);

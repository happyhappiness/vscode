                    SENTINEL_SIMFAILURE_CRASH_AFTER_PROMOTION;
                redisLog(REDIS_WARNING,"Failure simulation: this Sentinel "
                    "will crash after promoting the selected slave to master");
            } else {
                addReplyError(c,"Unknown failure simulation specified");
                return;

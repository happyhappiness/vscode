                                     CLUSTER_TODO_UPDATE_STATE);
            }
        } else {
            serverLog(REDIS_NOTICE,
                "Ignoring FAIL message from unknown node %.40s about %.40s",
                hdr->sender, hdr->data.fail.about.nodename);
        }

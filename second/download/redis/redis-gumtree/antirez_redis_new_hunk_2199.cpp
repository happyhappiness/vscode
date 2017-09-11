                addReplyError(c,
                    "Client reconfiguration script seems non existing or "
                    "non executable");
                if (changes) sentinelFlushConfig();
                return;
            }
            sdsfree(ri->client_reconfig_script);

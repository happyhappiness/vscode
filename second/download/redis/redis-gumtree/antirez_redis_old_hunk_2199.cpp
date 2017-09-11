                addReplyError(c,
                    "Client reconfiguration script seems non existing or "
                    "non executable");
                return;
            }
            sdsfree(ri->client_reconfig_script);

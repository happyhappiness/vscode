                                     "server reached MaxClients setting, consider"
                                     " raising the MaxClients setting");
                        reported = 1;
                    }
                } else {
                    static int reported = 0;

                    if (!reported) {
                        ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                                     ap_server_conf,
                                     "server is within MinSpareThreads of MaxClients, consider"
                                     " raising the MaxClients setting");
                        reported = 1;
                    }
                }
            }
            idle_spawn_rate = 1;
        }
        else {
            if (free_length > idle_spawn_rate) {
                free_length = idle_spawn_rate;
            }

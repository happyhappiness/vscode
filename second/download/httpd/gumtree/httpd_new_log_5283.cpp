ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf, APLOGNO(00162)
                    "server seems busy, (you may need "
                    "to increase StartServers, or Min/MaxSpareServers), "
                    "spawning %d children, there are %d idle, and "
                    "%d total children", retained->idle_spawn_rate,
                    idle_count, total_non_dead);
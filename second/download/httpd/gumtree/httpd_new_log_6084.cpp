ap_log_error(APLOG_MARK, APLOG_TRACE5, 0, ap_server_conf,
                             "Spawning new child: slot %d active / "
                             "total daemons: %d/%d",
                             free_slots[i], active_daemons,
                             retained->total_daemons);
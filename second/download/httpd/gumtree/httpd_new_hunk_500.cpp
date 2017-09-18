	/* terminate the free list */
	if (free_length == 0) {
	    /* only report this condition once */
	    static int reported = 0;

	    if (!reported) {
		ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf,
			    "server reached MaxClients setting, consider"
			    " raising the MaxClients setting");
		reported = 1;
	    }
	    idle_spawn_rate = 1;
	}
	else {
	    if (idle_spawn_rate >= 8) {
		ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf,
		    "server seems busy, (you may need "
		    "to increase StartServers, or Min/MaxSpareServers), "
		    "spawning %d children, there are %d idle, and "
		    "%d total children", idle_spawn_rate,
		    idle_count, total_non_dead);
	    }
	    for (i = 0; i < free_length; ++i) {
#ifdef TPF
        if (make_child(ap_server_conf, free_slots[i]) == -1) {
            if(free_length == 1) {
                shutdown_pending = 1;
                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, ap_server_conf,
                "No active child processes: shutting down");
            }
        }
#else
		make_child(ap_server_conf, free_slots[i]);
#endif /* TPF */

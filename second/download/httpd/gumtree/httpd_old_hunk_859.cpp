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
	    }
	    /* the next time around we want to spawn twice as many if this
	     * wasn't good enough, but not if we've just done a graceful

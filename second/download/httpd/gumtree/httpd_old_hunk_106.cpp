	ap_log_error(APLOG_MARK, APLOG_EMERG, server_conf,
		    "flock: LOCK_UN: Error freeing accept lock. Exiting!");
	clean_child_exit(APEXIT_CHILDFATAL);
    }
}

#else
/* Default --- no serialization.  Other methods *could* go here,
 * as #elifs...
 */
#if !defined(MULTITHREAD)
/* Multithreaded systems don't complete between processes for

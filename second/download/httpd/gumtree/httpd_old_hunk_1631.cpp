	}
    }

    /* clean up and return */
    result[res_pos] = 0;
#if MIME_MAGIC_DEBUG
    ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, r->server,
	     MODNAME ": rsl_strdup() %d chars: %s", res_pos - 1, result);
#endif
    return result;
}

/* states for the state-machine algorithm in magic_rsl_to_request() */

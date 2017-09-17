
    arg.r = r;
    arg.s = s;

    if (!ap_bspawn_child(r->pool, include_cmd_child, &arg,
			 kill_after_timeout, NULL, &script_in, NULL)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
		     "couldn't spawn include command");
        return -1;
    }

    ap_send_fb(script_in, r);
    ap_bclose(script_in);

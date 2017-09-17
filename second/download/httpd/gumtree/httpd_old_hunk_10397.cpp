                  ap_escape_shell_cmd(r->pool, arg_copy));
    }

    while (1) {
        if (!find_string(f, STARTING_SEQUENCE, r, printing)) {
            if (get_directive(f, directive, sizeof(directive), r->pool)) {
		ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
			    "mod_include: error reading directive in %s",
			    r->filename);
		ap_rputs(error, r);
                return;
            }
            if (!strcmp(directive, "if")) {

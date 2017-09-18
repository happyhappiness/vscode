
    if (m->module_index == -1) {
        m->module_index = total_modules++;
        dynamic_modules++;

        if (dynamic_modules > DYNAMIC_MODULE_LIMIT) {
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                         "%s: module \"%s\" could not be loaded, because"
                         " the dynamic", ap_server_argv0, m->name);
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                         "module limit was reached. Please increase "
                         "DYNAMIC_MODULE_LIMIT and recompile.");
            exit(1);
        }
    }


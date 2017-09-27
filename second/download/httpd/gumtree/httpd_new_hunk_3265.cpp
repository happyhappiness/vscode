        limit = atoi(arg2);

        if (limit <= 0) {
            return "The recursion limit must be greater than zero.";
        }
        if (limit < 4) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(00120)
                         "Limiting the subrequest depth to a very low level may"
                         " cause normal requests to fail.");
        }
    }

    conf->subreq_limit = limit;

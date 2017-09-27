ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, c->base_server,
        "mod_dumpio: %s [%s-%s] %" APR_OFF_T_FMT " readbytes",
         f->frec->name,
         whichmode(mode),
         ((block) == APR_BLOCK_READ) ? "blocking" : "nonblocking",
         readbytes);
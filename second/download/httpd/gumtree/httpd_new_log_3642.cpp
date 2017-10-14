ap_log_cerror(APLOG_MARK, APLOG_TRACE7, 0, c,
                  "mod_dumpio: %s [%s-%s] %" APR_OFF_T_FMT " readbytes",
                  f->frec->name,
                  whichmode(mode),
                  ((block) == APR_BLOCK_READ) ? "blocking" : "nonblocking",
                  readbytes);
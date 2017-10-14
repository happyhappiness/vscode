ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r,
                          "can't initialise input filter %s: %s",
                          f->frec->name,
                          (ctx->dc->onfail == 1) ? "removing" : "aborting");
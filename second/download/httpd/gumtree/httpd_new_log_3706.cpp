ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, APLOGNO(01470)
                          "can't initialise input filter %s: %s",
                          f->frec->name,
                          (ctx->dc->onfail == 1) ? "removing" : "aborting");
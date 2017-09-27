ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01467)
                          "can't initialise output filter %s: %s",
                          f->frec->name,
                          (ctx->dc->onfail == 1) ? "removing" : "aborting");
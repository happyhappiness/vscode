ap_log_cerror(APLOG_MARK, APLOG_TRACE7, rv, c,
                          "mod_dumpio:  %s (%s-%s): %s", f->frec->name,
                          (APR_BUCKET_IS_METADATA(b)) ? "metadata" : "data",
                          b->type->name, "error reading data");
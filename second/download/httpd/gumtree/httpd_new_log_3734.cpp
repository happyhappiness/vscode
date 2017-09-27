ap_log_cerror(APLOG_MARK, APLOG_TRACE7, 0, c,
                  "mod_dumpio:  %s (%s-%s): %" APR_SIZE_T_FMT " bytes",
                  f->frec->name,
                  (APR_BUCKET_IS_METADATA(b)) ? "metadata" : "data",
                  b->type->name,
                  b->length);
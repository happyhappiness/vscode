        for (b = APR_BRIGADE_FIRST(bb); b != APR_BRIGADE_SENTINEL(bb); b = APR_BUCKET_NEXT(b)) {
          dumpit(f, b, ptr);
        }
    } else {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE7, 0, c,
                      "mod_dumpio: %s - %d", f->frec->name, ret) ;
    }

    return APR_SUCCESS ;
}

static int dumpio_output_filter (ap_filter_t *f, apr_bucket_brigade *bb)

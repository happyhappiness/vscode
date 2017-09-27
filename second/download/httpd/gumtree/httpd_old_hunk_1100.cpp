        backref_t *re = ctx->intern->re;

        /* Handle $0 .. $9 from the last regex evaluated.
         * The choice of returning NULL strings on not-found,
         * v.s. empty strings on an empty match is deliberate.
         */
        if (!re) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                "regex capture $%" APR_SIZE_T_FMT " refers to no regex in %s",
                idx, r->filename);
            return NULL;
        }
        else {
            if (re->nsub < idx || idx >= AP_MAX_REG_MATCH) {
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                              "regex capture $%" APR_SIZE_T_FMT
                              " is out of range (last regex was: '%s') in %s",
                              idx, re->rexp, r->filename);
                return NULL;
            }

            if (re->match[idx].rm_so < 0 || re->match[idx].rm_eo < 0) {
                return NULL;
            }

            val = apr_pstrmemdup(ctx->dpool, re->source + re->match[idx].rm_so,
                                 re->match[idx].rm_eo - re->match[idx].rm_so);
        }
    }
    else {
        val = apr_table_get(r->subprocess_env, var);

        if (val == LAZY_VALUE) {
            val = add_include_vars_lazy(r, var);
        }
    }

    return val;
}


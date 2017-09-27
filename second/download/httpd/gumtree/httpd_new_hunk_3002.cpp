
        envlen += keylen;

        vallen = strlen(elts[i].val);

#ifdef FCGI_DUMP_ENV_VARS
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01062)
                      "sending env var '%s' value '%s'",
                      elts[i].key, elts[i].val);
#endif

        if (vallen >> 7 == 0) {
            envlen += 1;
        }

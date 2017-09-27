            /* if it doesn't contain "content", ignore, don't crash! */
            if (p != NULL) {
                while (*p) {
                    p += 7;
                    while (apr_isspace(*p))
                        ++p;
                    if (*p != '=')
                        continue;
                    while (*p && apr_isspace(*++p));
                    if ((*p == '\'') || (*p == '"')) {
                        delim = *p++;
                        for (q = p; *q != delim; ++q);
                    } else {
                        for (q = p; *q && !apr_isspace(*q) && (*q != '>'); ++q);
                    }
                    content = apr_pstrndup(r->pool, p, q-p);
                    break;
                }
            }
        }
        else if (!strncasecmp(header, "Content-Type", 12)) {
            ret = apr_palloc(r->pool, sizeof(meta));
            ret->start = pmatch[0].rm_so;
            ret->end = pmatch[0].rm_eo;
        }
        if (header && content) {
#ifndef GO_FASTER
            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                          "Adding header [%s: %s] from HTML META",
                          header, content); 

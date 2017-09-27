            r->filename = apr_pstrcat(r->pool, r->filename, "/", NULL);
        }
        return index_directory(r, d);
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Directory index forbidden by "
                      "Options directive: %s", r->filename);
        return HTTP_FORBIDDEN;
    }
}

static void register_hooks(apr_pool_t *p)
{

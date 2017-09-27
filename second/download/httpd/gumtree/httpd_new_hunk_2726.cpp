        if (r->filename[strlen(r->filename) - 1] != '/') {
            r->filename = apr_pstrcat(r->pool, r->filename, "/", NULL);
        }
        return index_directory(r, d);
    }
    else {
        const char *index_names = apr_table_get(r->notes, "dir-index-names");

        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01276)
                      "Cannot serve directory %s: No matching DirectoryIndex (%s) found, and "
                      "server-generated directory index forbidden by "
                      "Options directive",
                       r->filename,
                       index_names ? index_names : "none");
        return HTTP_FORBIDDEN;
    }
}

static void register_hooks(apr_pool_t *p)
{

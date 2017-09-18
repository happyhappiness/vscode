                != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rc, s, 
                         "mod_rewrite: could not open RewriteLog "
                         "file %s", fname);
            exit(1);
        }
        apr_file_set_inherit(conf->rewritelogfp);
    }
    return;
}

static void rewritelog(request_rec *r, int level, const char *text, ...)
{

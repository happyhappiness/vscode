        apr_file_read(fpout, &c, &nbytes);
    }
    buf[i] = '\0';

    /* give the lock back */
    if (rewrite_mapr_lock_acquire) {
        rv = apr_global_mutex_unlock(rewrite_mapr_lock_acquire);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "apr_global_mutex_unlock(rewrite_mapr_lock_acquire) "
                          "failed");
            return NULL; /* Maybe this should be fatal? */
        }
    }

    if (strcasecmp(buf, "NULL") == 0) {
        return NULL;
    }
    else {
        return apr_pstrdup(r->pool, buf);
    }
}

static void ap_register_rewrite_mapfunc(char *name, rewrite_mapfunc_t *func)
{
    apr_hash_set(mapfunc_hash, name, strlen(name), (const void *)func);
}

static char *rewrite_mapfunc_toupper(request_rec *r, char *key)
{
    char *value, *cp;


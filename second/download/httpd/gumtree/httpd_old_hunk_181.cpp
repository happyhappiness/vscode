        apr_file_read(fpout, &c, &nbytes);
    }
    buf[i] = '\0';

    /* give the lock back */
    if (rewrite_mapr_lock_acquire) {
        apr_global_mutex_unlock(rewrite_mapr_lock_acquire);
    }

    if (strcasecmp(buf, "NULL") == 0) {
        return NULL;
    }
    else {
        return apr_pstrdup(r->pool, buf);
    }
}

static char *lookup_map_internal(request_rec *r,
                                 char *(*func)(request_rec *, char *),
                                 char *key)
{
    /* currently we just let the function convert
       the key to a corresponding value */
    return func(r, key);
}

static char *rewrite_mapfunc_toupper(request_rec *r, char *key)
{
    char *value, *cp;


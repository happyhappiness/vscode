    apr_snprintf(str3, sizeof(str3),
                "%s %s [%s/sid#%lx][rid#%lx/%s%s] (%d) %s" APR_EOL_STR, str1,
                current_logtime(r), ap_get_server_name(r),
                (unsigned long)(r->server), (unsigned long)r,
                type, redir, level, str2);

    apr_global_mutex_lock(rewrite_log_lock);
    nbytes = strlen(str3);
    apr_file_write(conf->rewritelogfp, str3, &nbytes);
    apr_global_mutex_unlock(rewrite_log_lock);

    va_end(ap);
    return;
}

static char *current_logtime(request_rec *r)

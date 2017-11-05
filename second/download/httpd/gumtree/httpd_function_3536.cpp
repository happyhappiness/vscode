static char *lookup_map_program(request_rec *r, apr_file_t *fpin,
                                apr_file_t *fpout, char *key)
{
    char *buf;
    char c;
    apr_size_t i, nbytes, combined_len = 0;
    apr_status_t rv;
    const char *eol = APR_EOL_STR;
    apr_size_t eolc = 0;
    int found_nl = 0;
    result_list *buflist = NULL, *curbuf = NULL;

#ifndef NO_WRITEV
    struct iovec iova[2];
    apr_size_t niov;
#endif

    /* when `RewriteEngine off' was used in the per-server
     * context then the rewritemap-programs were not spawned.
     * In this case using such a map (usually in per-dir context)
     * is useless because it is not available.
     *
     * newlines in the key leave bytes in the pipe and cause
     * bad things to happen (next map lookup will use the chars
     * after the \n instead of the new key etc etc - in other words,
     * the Rewritemap falls out of sync with the requests).
     */
    if (fpin == NULL || fpout == NULL || ap_strchr(key, '\n')) {
        return NULL;
    }

    /* take the lock */
    if (rewrite_mapr_lock_acquire) {
        rv = apr_global_mutex_lock(rewrite_mapr_lock_acquire);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "apr_global_mutex_lock(rewrite_mapr_lock_acquire) "
                          "failed");
            return NULL; /* Maybe this should be fatal? */
        }
    }

    /* write out the request key */
#ifdef NO_WRITEV
    nbytes = strlen(key);
    apr_file_write(fpin, key, &nbytes);
    nbytes = 1;
    apr_file_write(fpin, "\n", &nbytes);
#else
    iova[0].iov_base = key;
    iova[0].iov_len = strlen(key);
    iova[1].iov_base = "\n";
    iova[1].iov_len = 1;

    niov = 2;
    apr_file_writev(fpin, iova, niov, &nbytes);
#endif

    buf = apr_palloc(r->pool, REWRITE_PRG_MAP_BUF + 1);

    /* read in the response value */
    nbytes = 1;
    apr_file_read(fpout, &c, &nbytes);
    do {
        i = 0;
        while (nbytes == 1 && (i < REWRITE_PRG_MAP_BUF)) {
            if (c == eol[eolc]) {
                if (!eol[++eolc]) {
                    /* remove eol from the buffer */
                    --eolc;
                    if (i < eolc) {
                        curbuf->len -= eolc-i;
                        i = 0;
                    }
                    else {
                        i -= eolc;
                    }
                    ++found_nl;
                    break;
                }
            }

            /* only partial (invalid) eol sequence -> reset the counter */
            else if (eolc) {
                eolc = 0;
            }

            /* catch binary mode, e.g. on Win32 */
            else if (c == '\n') {
                ++found_nl;
                break;
            }

            buf[i++] = c;
            apr_file_read(fpout, &c, &nbytes);
        }

        /* well, if there wasn't a newline yet, we need to read further */
        if (buflist || (nbytes == 1 && !found_nl)) {
            if (!buflist) {
                curbuf = buflist = apr_palloc(r->pool, sizeof(*buflist));
            }
            else if (i) {
                curbuf->next = apr_palloc(r->pool, sizeof(*buflist));
                curbuf = curbuf->next;

            }
            curbuf->next = NULL;

            if (i) {
                curbuf->string = buf;
                curbuf->len = i;
                combined_len += i;
                buf = apr_palloc(r->pool, REWRITE_PRG_MAP_BUF);
            }

            if (nbytes == 1 && !found_nl) {
                i = 0;
                continue;
            }
        }

        break;
    } while (1);

    /* concat the stuff */
    if (buflist) {
        char *p;

        p = buf = apr_palloc(r->pool, combined_len + 1); /* \0 */
        while (buflist) {
            if (buflist->len) {
                memcpy(p, buflist->string, buflist->len);
                p += buflist->len;
            }
            buflist = buflist->next;
        }
        *p = '\0';
        i = combined_len;
    }
    else {
        buf[i] = '\0';
    }

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

    /* catch the "failed" case */
    if (i == 4 && !strcasecmp(buf, "NULL")) {
        return NULL;
    }

    return buf;
}
static void dumpit(ap_filter_t *f, apr_bucket *b)
{
    conn_rec *c = f->c;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, c->base_server,
        "mod_dumpio:  %s (%s-%s): %" APR_SIZE_T_FMT " bytes",
                f->frec->name,
                (APR_BUCKET_IS_METADATA(b)) ? "metadata" : "data",
                b->type->name,
                b->length) ;

    if (!(APR_BUCKET_IS_METADATA(b))) {
        const char *buf;
        apr_size_t nbytes;
        char *obuf;
        if (apr_bucket_read(b, &buf, &nbytes, APR_BLOCK_READ) == APR_SUCCESS) {
            if (nbytes) {
                obuf = malloc(nbytes+1);    /* use pool? */
                memcpy(obuf, buf, nbytes);
                obuf[nbytes] = '\0';
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, c->base_server,
                     "mod_dumpio:  %s (%s-%s): %s",
                     f->frec->name,
                     (APR_BUCKET_IS_METADATA(b)) ? "metadata" : "data",
                     b->type->name,
                     obuf);
                free(obuf);
            }
        } else {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, c->base_server,
                 "mod_dumpio:  %s (%s-%s): %s",
                 f->frec->name,
                 (APR_BUCKET_IS_METADATA(b)) ? "metadata" : "data",
                 b->type->name,
                 "error reading data");
        }
    }
}
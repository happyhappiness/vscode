static void dumpit(ap_filter_t *f, apr_bucket *b)
{
    conn_rec *c = f->c;
    dumpio_conf_t *ptr =
    (dumpio_conf_t *) ap_get_module_config(c->base_server->module_config,
                                           &dumpio_module);

    ap_log_error(APLOG_MARK, ptr->loglevel, 0, c->base_server,
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
#if APR_CHARSET_EBCDIC
                ap_xlate_proto_from_ascii(obuf, nbytes);
#endif
                obuf[nbytes] = '\0';
                ap_log_error(APLOG_MARK, ptr->loglevel, 0, c->base_server,
                     "mod_dumpio:  %s (%s-%s): %s",
                     f->frec->name,
                     (APR_BUCKET_IS_METADATA(b)) ? "metadata" : "data",
                     b->type->name,
                     obuf);
                free(obuf);
            }
        } else {
            ap_log_error(APLOG_MARK, ptr->loglevel, 0, c->base_server,
                 "mod_dumpio:  %s (%s-%s): %s",
                 f->frec->name,
                 (APR_BUCKET_IS_METADATA(b)) ? "metadata" : "data",
                 b->type->name,
                 "error reading data");
        }
    }
}
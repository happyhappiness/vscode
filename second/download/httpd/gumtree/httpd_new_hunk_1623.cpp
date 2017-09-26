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

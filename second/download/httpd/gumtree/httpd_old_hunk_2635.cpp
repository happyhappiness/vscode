 * info about the data in the bucket as well as the data itself
 */
static void dumpit(ap_filter_t *f, apr_bucket *b, dumpio_conf_t *ptr)
{
    conn_rec *c = f->c;

    ap_log_error(APLOG_MARK, APLOG_TRACE7, 0, c->base_server,
        "mod_dumpio:  %s (%s-%s): %" APR_SIZE_T_FMT " bytes",
                f->frec->name,
                (APR_BUCKET_IS_METADATA(b)) ? "metadata" : "data",
                b->type->name,
                b->length) ;

    if (!(APR_BUCKET_IS_METADATA(b)))
    {
#if APR_CHARSET_EBCDIC
        char xlatebuf[dumpio_MAX_STRING_LEN + 1];
#endif
        const char *buf;
        apr_size_t nbytes;
        apr_size_t logbytes;
        apr_status_t rv = apr_bucket_read(b, &buf, &nbytes, APR_BLOCK_READ);

        if (rv == APR_SUCCESS)
        {
            while (nbytes)
            {
                logbytes = nbytes;
                if (logbytes > dumpio_MAX_STRING_LEN)
                    logbytes = dumpio_MAX_STRING_LEN;
                nbytes -= logbytes;

#if APR_CHARSET_EBCDIC
                memcpy(xlatebuf, buf, logbytes);
                ap_xlate_proto_from_ascii(xlatebuf, logbytes);
                xlatebuf[logbytes] = '\0';
                ap_log_error(APLOG_MARK, APLOG_TRACE7, 0, c->base_server,
                             "mod_dumpio:  %s (%s-%s): %s", f->frec->name,
                             (APR_BUCKET_IS_METADATA(b)) ? "metadata" : "data",
                             b->type->name, xlatebuf);
#else
                /* XXX: Seriously flawed; we do not pay attention to embedded
                 * \0's in the request body, these should be escaped; however,
                 * the logging function already performs a significant amount
                 * of escaping, and so any escaping would be double-escaped.
                 * The coding solution is to throw away the current logic
                 * within ap_log_error, and introduce new vformatter %-escapes
                 * for escaping text, and for binary text (fixed len strings).
                 */
                ap_log_error(APLOG_MARK | APLOG_NOERRNO, APLOG_TRACE7, 0, c->base_server,
                             "mod_dumpio:  %s (%s-%s): %.*s", f->frec->name,
                             (APR_BUCKET_IS_METADATA(b)) ? "metadata" : "data",
                             b->type->name, (int)logbytes, buf);
#endif
            }
        } else {
            ap_log_error(APLOG_MARK, APLOG_TRACE7, rv, c->base_server,
                         "mod_dumpio:  %s (%s-%s): %s", f->frec->name,
                         (APR_BUCKET_IS_METADATA(b)) ? "metadata" : "data",
                         b->type->name, "error reading data");
        }
    }
}

#define whichmode( mode ) \
 ( (( mode ) == AP_MODE_READBYTES) ? "readbytes" : \

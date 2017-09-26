    int i;    

    for (i = 0; i < len-1; i++) {
        readlen = 1;
        rv = apr_file_read(thefile, str+i, &readlen);

        if (rv != APR_SUCCESS && rv != APR_EOF)
            return rv;

        if (readlen == 0) {
            /* If we have bytes, defer APR_EOF to the next call */
            if (i > 0)
                rv = APR_SUCCESS;
            break;
        }
        
        if (str[i] == '\n') {
            i++; /* don't clobber this char below */
            break;
        }
    }
    str[i] = 0;
    return rv;
}

APR_DECLARE(apr_status_t) apr_file_flush(apr_file_t *thefile)
{
    if (thefile->buffered) {
        DWORD written = 0;
        apr_status_t rc = 0;

        if (thefile->direction == 1 && thefile->bufpos) {
            if (!WriteFile(thefile->filehand, thefile->buffer, thefile->bufpos, &written, NULL))
                rc = apr_get_os_error();
            thefile->filePtr += written;

            if (rc == 0)
                thefile->bufpos = 0;
        }

        return rc;
    }

    /* There isn't anything to do if we aren't buffering the output
     * so just return success.
     */
    return APR_SUCCESS; 
}

struct apr_file_printf_data {
    apr_vformatter_buff_t vbuff;
    apr_file_t *fptr;
    char *buf;
};

static int file_printf_flush(apr_vformatter_buff_t *buff)
{
    struct apr_file_printf_data *data = (struct apr_file_printf_data *)buff;

    if (apr_file_write_full(data->fptr, data->buf,
                            data->vbuff.curpos - data->buf, NULL)) {
        return -1;
    }

    data->vbuff.curpos = data->buf;
    return 0;
}

APR_DECLARE_NONSTD(int) apr_file_printf(apr_file_t *fptr, 
                                        const char *format, ...)
{
    struct apr_file_printf_data data;
    va_list ap;
    int count;

    data.buf = malloc(HUGE_STRING_LEN);
    if (data.buf == NULL) {
        return 0;
    }
    data.vbuff.curpos = data.buf;
    data.vbuff.endpos = data.buf + HUGE_STRING_LEN;
    data.fptr = fptr;
    va_start(ap, format);
    count = apr_vformatter(file_printf_flush,
                           (apr_vformatter_buff_t *)&data, format, ap);
    /* apr_vformatter does not call flush for the last bits */
    if (count >= 0) file_printf_flush((apr_vformatter_buff_t *)&data);

    va_end(ap);

    free(data.buf);
    return count;
}

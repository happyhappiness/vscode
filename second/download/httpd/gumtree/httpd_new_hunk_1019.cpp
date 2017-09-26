         */
        return APR_SUCCESS;
    }
    return rv;
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

    /* don't really need a HUGE_STRING_LEN anymore */
    data.buf = malloc(HUGE_STRING_LEN);
    if (data.buf == NULL) {
        return -1;
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

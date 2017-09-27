
            if (rc == 0)
                thefile->bufpos = 0;
        }

        return rc;
    } else {
        FlushFileBuffers(thefile->filehand);
        return APR_SUCCESS;
    }
}

static int printf_flush(apr_vformatter_buff_t *vbuff)
{
    /* I would love to print this stuff out to the file, but I will
     * get that working later.  :)  For now, just return.
     */
    return -1;
}

APR_DECLARE_NONSTD(int) apr_file_printf(apr_file_t *fptr, 
                                        const char *format, ...)
{
    int cc;
    va_list ap;
    char *buf;
    int len;

    buf = malloc(HUGE_STRING_LEN);
    if (buf == NULL) {
        return 0;
    }
    va_start(ap, format);
    len = apr_vsnprintf(buf, HUGE_STRING_LEN, format, ap);
    cc = apr_file_puts(buf, fptr);
    va_end(ap);
    free(buf);
    return (cc == APR_SUCCESS) ? len : -1;
}



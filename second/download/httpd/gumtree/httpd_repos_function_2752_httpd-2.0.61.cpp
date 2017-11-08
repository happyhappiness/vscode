static void check_sbcs(apr_xlate_t *convset)
{
    char inbuf[256], outbuf[256];
    char *inbufptr = inbuf;
    char *outbufptr = outbuf;
    apr_size_t inbytes_left, outbytes_left;
    int i;
    apr_size_t translated;

    for (i = 0; i < sizeof(inbuf); i++) {
        inbuf[i] = i;
    }

    inbytes_left = outbytes_left = sizeof(inbuf);
    translated = iconv(convset->ich, (ICONV_INBUF_TYPE)&inbufptr,
                       &inbytes_left, &outbufptr, &outbytes_left);

    if (translated != (apr_size_t)-1
        && inbytes_left == 0
        && outbytes_left == 0) {
        /* hurray... this is simple translation; save the table,
         * close the iconv descriptor
         */

        convset->sbcs_table = apr_palloc(convset->pool, sizeof(outbuf));
        memcpy(convset->sbcs_table, outbuf, sizeof(outbuf));
        iconv_close(convset->ich);
        convset->ich = (iconv_t)-1;

        /* TODO: add the table to the cache */
    }
    else {
        /* reset the iconv descriptor, since it's now in an undefined
         * state. */
        iconv_close(convset->ich);
        convset->ich = iconv_open(convset->topage, convset->frompage);
    }
}
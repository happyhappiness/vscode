static void ssl_io_data_dump(server_rec *srvr,
                             MODSSL_BIO_CB_ARG_TYPE *s,
                             long len)
{
    char buf[256];
    char tmp[64];
    int i, j, rows, trunc;
    unsigned char ch;

    trunc = 0;
    for(; (len > 0) && ((s[len-1] == ' ') || (s[len-1] == '\0')); len--)
        trunc++;
    rows = (len / DUMP_WIDTH);
    if ((rows * DUMP_WIDTH) < len)
        rows++;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, srvr,
            "+-------------------------------------------------------------------------+");
    for(i = 0 ; i< rows; i++) {
        apr_snprintf(tmp, sizeof(tmp), "| %04x: ", i * DUMP_WIDTH);
        apr_cpystrn(buf, tmp, sizeof(buf));
        for (j = 0; j < DUMP_WIDTH; j++) {
            if (((i * DUMP_WIDTH) + j) >= len)
                apr_cpystrn(buf+strlen(buf), "   ", sizeof(buf)-strlen(buf));
            else {
                ch = ((unsigned char)*((char *)(s) + i * DUMP_WIDTH + j)) & 0xff;
                apr_snprintf(tmp, sizeof(tmp), "%02x%c", ch , j==7 ? '-' : ' ');
                apr_cpystrn(buf+strlen(buf), tmp, sizeof(buf)-strlen(buf));
            }
        }
        apr_cpystrn(buf+strlen(buf), " ", sizeof(buf)-strlen(buf));
        for (j = 0; j < DUMP_WIDTH; j++) {
            if (((i * DUMP_WIDTH) + j) >= len)
                apr_cpystrn(buf+strlen(buf), " ", sizeof(buf)-strlen(buf));
            else {
                ch = ((unsigned char)*((char *)(s) + i * DUMP_WIDTH + j)) & 0xff;
                apr_snprintf(tmp, sizeof(tmp), "%c", ((ch >= ' ') && (ch <= '~')) ? ch : '.');
                apr_cpystrn(buf+strlen(buf), tmp, sizeof(buf)-strlen(buf));
            }
        }
        apr_cpystrn(buf+strlen(buf), " |", sizeof(buf)-strlen(buf));
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, srvr,
                     "%s", buf);
    }
    if (trunc > 0)
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, srvr,
                "| %04ld - <SPACES/NULS>", len + trunc);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, srvr,
            "+-------------------------------------------------------------------------+");
    return;
}
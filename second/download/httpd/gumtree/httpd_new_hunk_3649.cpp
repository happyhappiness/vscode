**  I/O Data Debugging
**  _________________________________________________________________
*/

#define DUMP_WIDTH 16

static void ssl_io_data_dump(server_rec *s,
                             const char *b,
                             long len)
{
    char buf[256];
    char tmp[64];
    int i, j, rows, trunc;
    unsigned char ch;

    trunc = 0;
    for(; (len > 0) && ((b[len-1] == ' ') || (b[len-1] == '\0')); len--)
        trunc++;
    rows = (len / DUMP_WIDTH);
    if ((rows * DUMP_WIDTH) < len)
        rows++;
    ap_log_error(APLOG_MARK, APLOG_TRACE7, 0, s,
            "+-------------------------------------------------------------------------+");
    for(i = 0 ; i< rows; i++) {
#if APR_CHARSET_EBCDIC
        char ebcdic_text[DUMP_WIDTH];
        j = DUMP_WIDTH;
        if ((i * DUMP_WIDTH + j) > len)
            j = len % DUMP_WIDTH;
        if (j == 0)
            j = DUMP_WIDTH;
        memcpy(ebcdic_text,(char *)(b) + i * DUMP_WIDTH, j);
        ap_xlate_proto_from_ascii(ebcdic_text, j);
#endif /* APR_CHARSET_EBCDIC */
        apr_snprintf(tmp, sizeof(tmp), "| %04x: ", i * DUMP_WIDTH);
        apr_cpystrn(buf, tmp, sizeof(buf));
        for (j = 0; j < DUMP_WIDTH; j++) {
            if (((i * DUMP_WIDTH) + j) >= len)
                apr_cpystrn(buf+strlen(buf), "   ", sizeof(buf)-strlen(buf));
            else {
                ch = ((unsigned char)*((char *)(b) + i * DUMP_WIDTH + j)) & 0xff;
                apr_snprintf(tmp, sizeof(tmp), "%02x%c", ch , j==7 ? '-' : ' ');
                apr_cpystrn(buf+strlen(buf), tmp, sizeof(buf)-strlen(buf));
            }
        }
        apr_cpystrn(buf+strlen(buf), " ", sizeof(buf)-strlen(buf));
        for (j = 0; j < DUMP_WIDTH; j++) {
            if (((i * DUMP_WIDTH) + j) >= len)
                apr_cpystrn(buf+strlen(buf), " ", sizeof(buf)-strlen(buf));
            else {
                ch = ((unsigned char)*((char *)(b) + i * DUMP_WIDTH + j)) & 0xff;
#if APR_CHARSET_EBCDIC
                apr_snprintf(tmp, sizeof(tmp), "%c", (ch >= 0x20 && ch <= 0x7F) ? ebcdic_text[j] : '.');
#else /* APR_CHARSET_EBCDIC */
                apr_snprintf(tmp, sizeof(tmp), "%c", ((ch >= ' ') && (ch <= '~')) ? ch : '.');
#endif /* APR_CHARSET_EBCDIC */
                apr_cpystrn(buf+strlen(buf), tmp, sizeof(buf)-strlen(buf));
            }
        }
        apr_cpystrn(buf+strlen(buf), " |", sizeof(buf)-strlen(buf));
        ap_log_error(APLOG_MARK, APLOG_TRACE7, 0, s, "%s", buf);
    }
    if (trunc > 0)
        ap_log_error(APLOG_MARK, APLOG_TRACE7, 0, s,
                "| %04ld - <SPACES/NULS>", len + trunc);
    ap_log_error(APLOG_MARK, APLOG_TRACE7, 0, s,
            "+-------------------------------------------------------------------------+");
    return;
}

long ssl_io_data_cb(BIO *bio, int cmd,
                    const char *argp,

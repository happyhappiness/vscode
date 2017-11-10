static char *ftp_get_PWD(request_rec *r, conn_rec *ftp_ctrl, apr_bucket_brigade *bb)
{
    char *cwd = NULL;
    char *ftpmessage = NULL;

    /* responses: 257, 500, 501, 502, 421, 550 */
    /* 257 "<directory-name>" <commentary> */
    /* 421 Service not available, closing control connection. */
    /* 500 Syntax error, command unrecognized. */
    /* 501 Syntax error in parameters or arguments. */
    /* 502 Command not implemented. */
    /* 550 Requested action not taken. */
    switch (proxy_ftp_command("PWD" CRLF, r, ftp_ctrl, bb, &ftpmessage)) {
        case -1:
        case 421:
        case 550:
            ap_proxyerror(r, HTTP_BAD_GATEWAY,
                             "Failed to read PWD on ftp server");
            break;

        case 257: {
            const char *dirp = ftpmessage;
            cwd = ap_getword_conf(r->pool, &dirp);
        }
    }
    return cwd;
}
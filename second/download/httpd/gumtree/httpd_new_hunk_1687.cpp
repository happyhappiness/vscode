                ;
            ftpmessage[j] = '\0';
            if (ftpmessage[0] != '\0')
                 size = ftpmessage; /* already pstrdup'ed: no copy necessary */
        }
        else if (rc == 550) {    /* Not a regular file */
            ap_log_error(APLOG_MARK, APLOG_TRACE4, 0, r->server,
                         "proxy: FTP: SIZE shows this is a directory");
            dirlisting = 1;
            rc = proxy_ftp_command(apr_pstrcat(p, "CWD ",
                           ftp_escape_globbingchars(p, path, fdconf), CRLF, NULL),
                           r, origin, bb, &ftpmessage);
            /* possible results: 250, 421, 500, 501, 502, 530, 550 */
            /* 250 Requested file action okay, completed. */
            /* 421 Service not available, closing control connection. */
            /* 500 Syntax error, command unrecognized. */
            /* 501 Syntax error in parameters or arguments. */

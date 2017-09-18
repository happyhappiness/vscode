                ;
            ftpmessage[j] = '\0';
            if (ftpmessage[0] != '\0')
                 size = ftpmessage; /* already pstrdup'ed: no copy necessary */
        }
        else if (rc == 550) {    /* Not a regular file */
            ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, r->server,
                             "proxy: FTP: SIZE shows this is a directory");
            dirlisting = 1;
            rc = proxy_ftp_command(apr_pstrcat(p, "CWD ", 
                           ftp_escape_globbingchars(p, path), CRLF, NULL),
                           r, origin, bb, &ftpmessage);
            /* possible results: 250, 421, 500, 501, 502, 530, 550 */

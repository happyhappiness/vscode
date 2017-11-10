static char *apr_os_strerror(char *buf, apr_size_t bufsize, apr_status_t errcode)
{
    apr_size_t len=0, i;

#ifndef NETWARE
#ifndef _WIN32_WCE
    len = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM 
                      | FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL,
                        errcode,
                        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), /* Default language */
                        buf,
                        (DWORD)bufsize,
                        NULL);
#else /* _WIN32_WCE speaks unicode */
     LPTSTR msg = (LPTSTR) buf;
     len = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM 
                       | FORMAT_MESSAGE_IGNORE_INSERTS,
                         NULL,
                         errcode,
                         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), /* Default language */
                         msg,
                         (DWORD) (bufsize/sizeof(TCHAR)),
                         NULL);
     /* in-place convert to US-ASCII, substituting '?' for non ASCII   */
     for(i = 0; i <= len; i++) {
        if (msg[i] < 0x80 && msg[i] >= 0) {
            buf[i] = (char) msg[i];
        } else {
            buf[i] = '?';
        }
    }
#endif
#endif

    if (!len) {
        for (i = 0; gaErrorList[i].msg; ++i) {
            if (gaErrorList[i].code == errcode) {
                apr_cpystrn(buf, gaErrorList[i].msg, bufsize);
                len = strlen(buf);
                break;
            }
        }
    }

    if (len) {
        /* FormatMessage put the message in the buffer, but it may
         * have embedded a newline (\r\n), and possible more than one.
         * Remove the newlines replacing them with a space. This is not
         * as visually perfect as moving all the remaining message over,
         * but more efficient.
         */
        i = len;
        while (i) {
            i--;
            if ((buf[i] == '\r') || (buf[i] == '\n'))
                buf[i] = ' ';
        }
    }
    else {
        /* Windows didn't provide us with a message.  Even stuff like                    * WSAECONNREFUSED won't get a message.
         */
        apr_snprintf(buf, bufsize, "Unrecognized Win32 error code %d", errcode);
    }

    return buf;
}
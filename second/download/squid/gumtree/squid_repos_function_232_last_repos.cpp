void
read_reply(int fd, void *data)
{
    struct _request *r = data;
    static unsigned char buf[READ_BUF_SZ];
    int len;
    int used = 0;
    if ((len = read(fd, buf, READ_BUF_SZ)) <= 0) {
        fd_close(fd);
        reqpersec++;
        nrequests++;
        return;
    }
    total_bytes_read += len;
    if (r->headfound < 2) {
        char *p, *header = NULL;
        int oldlen = strlen(r->buf);
        int newlen = oldlen + len;
        assert(oldlen <= READ_BUF_SZ);
        memcpy(r->buf + oldlen, buf, len);
        r->buf[newlen + 1] = '\0';
        for (p = r->buf; r->headfound < 2 && used < newlen; p++, used++) {
            switch (*p) {
            case '\n':
                r->headfound++;
                if (!header)
                    break;
                /* Decode header */
                if (strncmp(header, "HTTP", 4) == 0)
                    r->status = atoi(header + 8);
                else if (strncasecmp(header, "Content-Length:", 15) == 0)
                    r->content_length = atoi(header + 15);
                else if (strncasecmp(header, "X-Request-URI:", 14) == 0) {
                    /* Check URI */
                    if (strncmp(r->url, header + 15, strcspn(header + 15, "\r\n"))) {
                        char url[8192];
                        strncpy(url, header + 15, strcspn(header + 15, "\r\n"));
                        url[strcspn(header + 15, "\r\n")] = '\n';
                        fprintf(stderr, "ERROR: Sent %s received %s\n",
                                r->url, url);
                    }
                }
                header = NULL;
                break;
            case '\r':
                break;
            default:
                r->headfound = 0;
                if (!header)
                    header = p;
                break;
            }
        }
        if (header) {
            memmove(r->buf, header, newlen - (header - r->buf) + 1);
        }
        assert(used >= oldlen);
        used -= oldlen;
    }
    r->bodysize += len - used;
    if (opt_checksum) {
        for (; used < len; used++) {
            r->sum += buf[used];
        }
    }
}
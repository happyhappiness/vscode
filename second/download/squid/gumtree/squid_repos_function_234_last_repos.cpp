struct _request *
request(char *urlin) {
    int s = -1, f = -1;
    char buf[4096];
    char msg[8192];
    char *method, *url, *file, *size, *checksum, *status;
    char *host;
    char urlbuf[8192];
    int len, len2;
    time_t w;
    struct stat st;
    struct sockaddr_in S;
    struct _request *r;
    if (*urlin == '\0')
        return NULL;
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return NULL;
    }
    memset(&S, '\0', sizeof(struct sockaddr_in));
    S.sin_family = AF_INET;
    S.sin_port = htons(proxy_port);
    S.sin_addr.s_addr = inet_addr(proxy_addr);
    if (connect(s, (struct sockaddr *) &S, sizeof(S)) < 0) {
        close(s);
        perror("connect");
        return NULL;
    }
    strcpy(urlbuf, urlin);
    method = strtok(urlbuf, " ");
    url = strtok(NULL, " ");
    status = strtok(NULL, " ");
    file = strtok(NULL, " ");
    size = strtok(NULL, " ");
    checksum = strtok(NULL, " ");
    if (!url) {
        url = method;
        method = "GET";
    }
    if (!file)
        file = "-";
    if (!size)
        size = "-";
    if (!checksum)
        checksum = "-";
    r = calloc(1, sizeof *r);
    assert(r != NULL);
    r->url = xstrdup(url);
    assert(r->url);
    strcpy(r->method, method);
    strcpy(r->requestbodyfile, file);
    r->fd = s;
    if (size && strcmp(size, "-") != 0)
        r->validsize = atoi(size);
    else
        r->validsize = -1;  /* Unknown */
    if (checksum && strcmp(checksum, "-") != 0)
        r->validsum = strtoul(checksum, NULL, 0);
    if (status)
        r->validstatus = atoi(status);
    r->content_length = -1; /* Unknown */
    if (opt_accel) {
        host = strchr(url, '/') + 2;
        url = strchr(host, '/');
    } else {
        host = NULL;
    }
    snprintf(msg, sizeof(msg)-1, "%s %s HTTP/1.0\r\n", method, url);
    if (host) {
        url[0] = '\0';
        snprintf(buf, sizeof(buf)-1, "Host: %s\r\n", host);
        strcat(msg, buf);
        url[0] = '/';
    }
    strcat(msg, "Accept: */*\r\n");
    if (opt_ims && (lrand48() & 0x03) == 0) {
        w = time(NULL) - (lrand48() & 0x3FFFF);
        snprintf(buf, sizeof(buf)-1, "If-Modified-Since: %s\r\n", mkrfc850(&w));
        strcat(msg, buf);
    }
    if (file && strcmp(file, "-") != 0) {
        f = open(file, O_RDONLY);
        if (f < 0) {
            perror("open file");
            exit(1);
        }
        fstat(f, &st);
        snprintf(buf, sizeof(buf)-1, "Content-Length: %d\r\n", (int) st.st_size);
        strcat(msg, buf);
    }
    if (opt_range && (lrand48() & 0x03) == 0) {
        int len;
        int count = 0;
        strcat(msg, "Range: bytes=");
        while (((len = (int) lrand48()) & 0x03) == 0 || !count) {
            const int offset = (int) lrand48();
            if (count)
                strcat(msg, ",");
            switch (lrand48() & 0x03) {
            case 0:
                snprintf(buf, sizeof(buf)-1, "-%d", len);
                break;
            case 1:
                snprintf(buf, sizeof(buf)-1, "%d-", offset);
                break;
            default:
                snprintf(buf, sizeof(buf)-1, "%d-%d", offset, offset + len);
                break;
            }
            strcat(msg, buf);
            count++;
        }
        strcat(msg, "\r\n");
    }
    strcat(msg, custom_header);
    strcat(msg, "\r\n");
    len = strlen(msg);
    if ((len2 = write(s, msg, len)) != len) {
        close(s);
        perror("write request");
        free_request(r);
        return NULL;
    } else
        total_bytes_written += len2;
    if (f >= 0) {
        while ((len = read(f, buf, sizeof(buf))) > 0) {
            len2 = write(s, buf, len);
            if (len2 < 0) {
                perror("write body");
                close(s);
                free_request(r);
            }
        }
        if (len < 0) {
            perror("read body");
            exit(1);
        }
    }
    /*
     * if (fcntl(s, F_SETFL, O_NDELAY) < 0)
     * perror("fcntl O_NDELAY");
     */
    return r;
}
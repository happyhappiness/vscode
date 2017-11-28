static int
authenticate(int socket_fd, const char *username, const char *passwd)
{
    AUTH_HDR *auth;
    unsigned short total_length;
    u_char *ptr;
    int length;
    char passbuf[MAXPASS];
    u_char md5buf[256];
    int secretlen;
    u_char cbc[AUTH_VECTOR_LEN];
    int i, j;
    u_int32_t ui;
    struct sockaddr_in saremote;
    fd_set readfds;
    socklen_t salen;
    int retry = retries;

    /*
     *    Build an authentication request
     */
    auth = (AUTH_HDR *) send_buffer;
    auth->code = PW_AUTHENTICATION_REQUEST;
    auth->id = ++request_id;
    random_vector(vector);
    memcpy(auth->vector, vector, AUTH_VECTOR_LEN);
    total_length = AUTH_HDR_LEN;
    ptr = auth->data;

    /*
     *    User Name
     */
    *ptr++ = PW_USER_NAME;
    length = strlen(username);
    if (length > MAXPWNAM) {
        length = MAXPWNAM;
    }
    *ptr++ = length + 2;
    memcpy(ptr, username, length);
    ptr += length;
    total_length += length + 2;

    /*
     *    Password
     */
    length = strlen(passwd);
    if (length > MAXPASS) {
        length = MAXPASS;
    }
    memset(passbuf, 0, MAXPASS);
    memcpy(passbuf, passwd, length);

    /*
     * Length is rounded up to multiple of 16,
     * and the password is encoded in blocks of 16
     * with cipher block chaining
     */
    length = ((length / AUTH_VECTOR_LEN) + 1) * AUTH_VECTOR_LEN;

    *ptr++ = PW_PASSWORD;
    *ptr++ = length + 2;

    secretlen = strlen(secretkey);
    /* Set up the Cipher block chain */
    memcpy(cbc, auth->vector, AUTH_VECTOR_LEN);
    for (j = 0; j < length; j += AUTH_VECTOR_LEN) {
        /* Calculate the MD5 Digest */
        strcpy((char *) md5buf, secretkey);
        memcpy(md5buf + secretlen, cbc, AUTH_VECTOR_LEN);
        md5_calc(cbc, md5buf, secretlen + AUTH_VECTOR_LEN);

        /* Xor the password into the MD5 digest */
        for (i = 0; i < AUTH_VECTOR_LEN; i++) {
            *ptr++ = (cbc[i] ^= passbuf[j + i]);
        }
    }
    total_length += length + 2;

    *ptr++ = PW_NAS_PORT_ID;
    *ptr++ = 6;

    ui = htonl(nasport);
    memcpy(ptr, &ui, 4);
    ptr += 4;
    total_length += 6;

    *ptr++ = PW_NAS_PORT_TYPE;
    *ptr++ = 6;

    ui = htonl(nasporttype);
    memcpy(ptr, &ui, 4);
    ptr += 4;
    total_length += 6;

    if (*identifier) {
        int len = strlen(identifier);
        *ptr++ = PW_NAS_ID;
        *ptr++ = len + 2;
        memcpy(ptr, identifier, len);
        ptr += len;
        total_length += len + 2;
    } else {
        *ptr++ = PW_NAS_IP_ADDRESS;
        *ptr++ = 6;

        ui = htonl(nas_ipaddr);
        memcpy(ptr, &ui, 4);
        ptr += 4;
        total_length += 6;
    }

    /* Klaus Weidner <kw@w-m-p.com> changed this
     * from htonl to htons. It might have caused
     * you trouble or not. That depends on the byte
     * order of your system.
     * The symptom was that the radius server
     * ignored the requests, because they had zero
     * length according to the data header.
     */
    auth->length = htons(total_length);

    while (retry--) {
        int time_spent;
        struct timeval sent;
        /*
         *    Send the request we've built.
         */
        gettimeofday(&sent, NULL);
        send(socket_fd, (char *) auth, total_length, 0);
        while ((time_spent = time_since(&sent)) < 1000000) {
            struct timeval tv;
            int rc, len;
            if (!time_spent) {
                tv.tv_sec = 1;
                tv.tv_usec = 0;
            } else {
                tv.tv_sec = 0;
                tv.tv_usec = 1000000 - time_spent;
            }
            FD_ZERO(&readfds);
            FD_SET(socket_fd, &readfds);
            if (select(socket_fd + 1, &readfds, NULL, NULL, &tv) == 0)	/* Select timeout */
                break;
            salen = sizeof(saremote);
            len = recvfrom(socket_fd, recv_buffer, sizeof(i_recv_buffer),
                           0, (struct sockaddr *) &saremote, &salen);

            if (len < 0)
                continue;

            rc = result_recv(saremote.sin_addr.s_addr, saremote.sin_port, recv_buffer, len);
            if (rc == 0)
                return 1;
            if (rc == 1)
                return 0;
        }
    }

    fprintf(stderr, "%s: No response from RADIUS server\n", progname);

    return 0;
}
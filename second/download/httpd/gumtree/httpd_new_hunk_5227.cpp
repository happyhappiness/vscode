    reqlen = strlen(request);

    /*
     * Combine headers and (optional) post file into one continuous buffer
     */
    if (send_body) {
        char *buff = xmalloc(postlen + reqlen + 1);
        strcpy(buff, request);
        memcpy(buff + reqlen, postdata, postlen);
        request = buff;
    }

#ifdef NOT_ASCII

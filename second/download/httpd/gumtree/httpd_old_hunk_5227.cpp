    reqlen = strlen(request);

    /*
     * Combine headers and (optional) post file into one continuous buffer
     */
    if (send_body) {
        char *buff = malloc(postlen + reqlen + 1);
        if (!buff) {
            fprintf(stderr, "error creating request buffer: out of memory\n");
            return;
        }
        strcpy(buff, request);
        memcpy(buff + reqlen, postdata, postlen);
        request = buff;
    }

#ifdef NOT_ASCII

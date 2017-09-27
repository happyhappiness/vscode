    reqlen = strlen(request);

    /*
     * Combine headers and (optional) post file into one contineous buffer
     */
    if (posting == 1) {
	char *buff = malloc(postlen + reqlen + 1);
        if (!buff) {
            fprintf(stderr, "error creating request buffer: out of memory\n");
            return;
        }
	strcpy(buff, request);
	strcpy(buff + reqlen, postdata);
	request = buff;
    }

#ifdef NOT_ASCII

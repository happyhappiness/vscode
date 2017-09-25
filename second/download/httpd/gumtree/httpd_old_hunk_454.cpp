    reqlen = strlen(request);

    /*
     * Combine headers and (optional) post file into one contineous buffer
     */
    if (posting == 1) {
	char *buff = (char *) malloc(postlen + reqlen + 1);
	strcpy(buff, request);
	strcpy(buff + reqlen, postdata);
	request = buff;
    }

#ifdef NOT_ASCII

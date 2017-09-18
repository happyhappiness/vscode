
    s = string;
    /* keep space for \0 byte */
    while (*s) {
        if (*s == '<') {
	    if (close) {
                ap_rputs("&lt;/,", r);
	    } else {
                ap_rputs("&lt;", r);
	    }
        }
        else if (*s == '>') {
            ap_rputs("&gt;", r);

     * a string are exactly the same as what the user typed.) */
    len = snprintf(buf,sizeof(buf),"%.17Lf", value);
    /* Now remove trailing zeroes after the '.' */
    if ((p = strchr(buf,'.')) != NULL) {
        p = buf+len-1;
        while(*p == '0') {
            p--;
            len--;

     * that is "non surprising" for the user (that is, most small decimal
     * numbers will be represented in a way that when converted back into
     * a string are exactly the same as what the user typed.) */
    len = snprintf(buf,sizeof(buf),"%.17Lf", value);
    /* Now remove trailing zeroes after the '.' */
    if (strchr(buf,'.') != NULL) {
        char *p = buf+len-1;
        while(*p == '0') {
            p--;
            len--;
        }
        if (*p == '.') len--;
    }
    return createStringObject(buf,len);
}

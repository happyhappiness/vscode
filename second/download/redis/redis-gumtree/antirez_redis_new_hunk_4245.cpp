    return 0;
}

/* Write binary-safe string into a file in the bulkformat
 * $<count>\r\n<payload>\r\n */
static int fwriteBulkString(FILE *fp, char *s, unsigned long len) {
    char buf[128];

    snprintf(buf,sizeof(buf),"$%ld\r\n",(unsigned long)len);
    if (fwrite(buf,strlen(buf),1,fp) == 0) return 0;
    if (len && fwrite(s,len,1,fp) == 0) return 0;
    if (fwrite("\r\n",2,1,fp) == 0) return 0;
    return 1;
}

/* Write a double value in bulk format $<count>\r\n<payload>\r\n */
static int fwriteBulkDouble(FILE *fp, double d) {
    char buf[128], dbuf[128];

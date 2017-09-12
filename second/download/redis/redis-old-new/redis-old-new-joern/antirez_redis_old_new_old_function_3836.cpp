static int fwriteBulkString(FILE *fp, char *s, unsigned long len) {
    char buf[128];

    snprintf(buf,sizeof(buf),"$%ld\r\n",(unsigned long)len);
    if (fwrite(buf,strlen(buf),1,fp) == 0) return 0;
    if (len && fwrite(s,len,1,fp) == 0) return 0;
    if (fwrite("\r\n",2,1,fp) == 0) return 0;
    return 1;
}
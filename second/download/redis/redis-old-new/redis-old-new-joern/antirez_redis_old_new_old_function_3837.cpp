static int fwriteBulkLong(FILE *fp, long l) {
    char buf[128], lbuf[128];

    snprintf(lbuf,sizeof(lbuf),"%ld\r\n",l);
    snprintf(buf,sizeof(buf),"$%lu\r\n",(unsigned long)strlen(lbuf)-2);
    if (fwrite(buf,strlen(buf),1,fp) == 0) return 0;
    if (fwrite(lbuf,strlen(lbuf),1,fp) == 0) return 0;
    return 1;
}
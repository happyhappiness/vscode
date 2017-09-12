static int fwriteBulkLongLong(FILE *fp, long long l) {
    char bbuf[128], lbuf[128];
    unsigned int blen, llen;
    llen = ll2string(lbuf,32,l);
    blen = snprintf(bbuf,sizeof(bbuf),"$%u\r\n%s\r\n",llen,lbuf);
    if (fwrite(bbuf,blen,1,fp) == 0) return 0;
    return 1;
}
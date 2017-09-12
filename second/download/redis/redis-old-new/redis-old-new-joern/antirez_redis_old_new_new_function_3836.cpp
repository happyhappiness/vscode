static int fwriteBulkString(FILE *fp, char *s, unsigned long len) {
    char cbuf[128];
    int clen;
    cbuf[0] = '$';
    clen = 1+ll2string(cbuf+1,sizeof(cbuf)-1,len);
    cbuf[clen++] = '\r';
    cbuf[clen++] = '\n';
    if (fwrite(cbuf,clen,1,fp) == 0) return 0;
    if (len > 0 && fwrite(s,len,1,fp) == 0) return 0;
    if (fwrite("\r\n",2,1,fp) == 0) return 0;
    return 1;
}
    char buf[128];
    size_t len;

    len = snprintf(buf,sizeof(buf),":%ld\r\n",l);
    addReplySds(c,sdsnewlen(buf,len));
}

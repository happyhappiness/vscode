    char buf[32], *endptr;
    long value;
    int slen;
    
    value = strtol(s, &endptr, 10);
    if (endptr[0] != '\0') return REDIS_ERR;
    slen = snprintf(buf,32,"%ld",value);

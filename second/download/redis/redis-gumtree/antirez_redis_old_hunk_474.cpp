
    if ((string2ll(p+1,strlen(p+1),&llbits)) == 0 ||
        llbits < 1 ||
        (*sign == 1 && llbits > 63) ||
        (*sign == 0 && llbits > 64))
    {
        addReplyError(c,err);
        return C_ERR;

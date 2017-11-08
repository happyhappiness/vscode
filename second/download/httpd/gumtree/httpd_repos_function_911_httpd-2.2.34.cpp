DH *ssl_dh_GetTmpParam(int nKeyLen)
{
    unsigned n;

    for (n = 0; n < sizeof(dhparams)/sizeof(dhparams[0]); n++)
        if (nKeyLen >= dhparams[n].min)
            return dhparams[n].dh;
        
    return NULL; /* impossible to reach. */
}
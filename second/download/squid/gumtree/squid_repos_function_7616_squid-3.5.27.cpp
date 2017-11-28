const char *
xgai_strerror (int ecode)
{
    static const char *eai_descr[] = {
        "no error",
        "address family for nodename not supported",    /* EAI_ADDRFAMILY */
        "temporary failure in name resolution",     /* EAI_AGAIN */
        "invalid value for ai_flags",           /* EAI_BADFLAGS */
        "non-recoverable failure in name resolution",   /* EAI_FAIL */
        "ai_family not supported",          /* EAI_FAMILY */
        "memory allocation failure",            /* EAI_MEMORY */
        "no address associated with nodename",      /* EAI_NODATA */
        "nodename nor servname provided, or not known", /* EAI_NONAME */
        "servname not supported for ai_socktype",       /* EAI_SERVICE */
        "ai_socktype not supported",            /* EAI_SOCKTYPE */
        "system error returned in errno",           /* EAI_SYSTEM */
        "argument buffer overflow",         /* EAI_OVERFLOW */
    };

    if (ecode < 0 || ecode > (int) (sizeof eai_descr/ sizeof eai_descr[0]))
        return "unknown error";
    return eai_descr[ecode];
}
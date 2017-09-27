        return -1;
#endif
#endif
    }
}

static unsigned long ssl_util_thr_id(void)
{
    /* OpenSSL needs this to return an unsigned long.  On OS/390, the pthread
     * id is a structure twice that big.  Use the TCB pointer instead as a
     * unique unsigned long.
     */

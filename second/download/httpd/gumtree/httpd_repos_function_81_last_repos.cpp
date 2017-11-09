static long ssl_print_cb(BIO *bio,int cmd,const char *argp,int argi,long argl,long ret)
{
    BIO *out;

    out=(BIO *)BIO_get_callback_arg(bio);
    if (out == NULL) return(ret);

    if (cmd == (BIO_CB_READ|BIO_CB_RETURN)) {
        BIO_printf(out,"read from %p [%p] (%d bytes => %ld (0x%lX))\n",
                   bio, argp, argi, ret, ret);
        BIO_dump(out,(char *)argp,(int)ret);
        return(ret);
    }
    else if (cmd == (BIO_CB_WRITE|BIO_CB_RETURN)) {
        BIO_printf(out,"write to %p [%p] (%d bytes => %ld (0x%lX))\n",
                   bio, argp, argi, ret, ret);
        BIO_dump(out,(char *)argp,(int)ret);
    }
    return ret;
}
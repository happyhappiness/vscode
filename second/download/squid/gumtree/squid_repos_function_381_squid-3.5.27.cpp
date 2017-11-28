void
krb5_cleanup()
{
    if (kparam.context) {
        if (kparam.cc)
            krb5_cc_destroy(kparam.context, kparam.cc);
        krb5_free_context(kparam.context);
    }
}
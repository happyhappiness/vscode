void
krb5_cleanup()
{
    if (kparam.context)
        for (int i=0; i<MAX_DOMAINS; i++) {
            if (kparam.cc[i])
                krb5_cc_destroy(kparam.context, kparam.cc[i]);
            safe_free(kparam.mem_ccache[i]);
        }
    krb5_free_context(kparam.context);
}
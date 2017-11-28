void krb5_cleanup() {
        debugs(11, 5, HERE << "Cleanup kerberos context");
        if (kparam.context) {
            if (kparam.cc)
                krb5_cc_destroy(kparam.context, kparam.cc);
            kparam.cc = NULL;
            krb5_free_context(kparam.context);
            kparam.context = NULL;
        }
    }
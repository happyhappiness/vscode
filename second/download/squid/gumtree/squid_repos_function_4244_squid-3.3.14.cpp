static void
mimicExtensions(Ssl::X509_Pointer & cert, Ssl::X509_Pointer const & mimicCert)
{
    static int extensions[]= {
        NID_key_usage,
        NID_ext_key_usage,
        NID_basic_constraints,
        0
    };

    int nid;
    for (int i = 0; (nid = extensions[i]) != 0; ++i) {
        const int pos = X509_get_ext_by_NID(mimicCert.get(), nid, -1);
        if (X509_EXTENSION *ext = X509_get_ext(mimicCert.get(), pos))
            X509_add_ext(cert.get(), ext, -1);
    }

    // We could also restrict mimicking of the CA extension to CA:FALSE
    // because Squid does not generate valid fake CA certificates.
}
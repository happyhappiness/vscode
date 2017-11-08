BOOL SSL_X509_isSGC(X509 *cert)
{
    int ext_nid;
    EXTENDED_KEY_USAGE *sk;
    BOOL is_sgc;
    int i;

    is_sgc = FALSE;
    sk = X509_get_ext_d2i(cert, NID_ext_key_usage, NULL, NULL);
    if (sk) {
        for (i = 0; i < sk_ASN1_OBJECT_num(sk); i++) {
            ext_nid = OBJ_obj2nid(sk_ASN1_OBJECT_value(sk, i));
            if (ext_nid == NID_ms_sgc || ext_nid == NID_ns_sgc) {
                is_sgc = TRUE;
                break;
            }
        }
    EXTENDED_KEY_USAGE_free(sk);
    }
    return is_sgc;
}
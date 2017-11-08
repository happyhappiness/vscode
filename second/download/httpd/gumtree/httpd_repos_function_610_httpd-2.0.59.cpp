BOOL SSL_X509_isSGC(X509 *cert)
{
#ifdef HAVE_SSL_X509V3_EXT_d2i
    X509_EXTENSION *ext;
    int ext_nid;
    STACK *sk;
    BOOL is_sgc;
    int idx;
    int i;
    
    is_sgc = FALSE;
    idx = X509_get_ext_by_NID(cert, NID_ext_key_usage, -1);
    if (idx >= 0) {
        ext = X509_get_ext(cert, idx);
        if ((sk = (STACK *)X509V3_EXT_d2i(ext)) != NULL) {
            for (i = 0; i < sk_num(sk); i++) {
                ext_nid = OBJ_obj2nid((ASN1_OBJECT *)sk_value(sk, i));
                if (ext_nid == NID_ms_sgc || ext_nid == NID_ns_sgc) {
                    is_sgc = TRUE;
                    break;
                }
            }
        }
    }
    return is_sgc;
#else
    return FALSE;
#endif
}
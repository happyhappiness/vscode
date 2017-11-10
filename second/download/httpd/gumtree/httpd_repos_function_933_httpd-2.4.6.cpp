static char *ssl_var_lookup_ssl_cert(apr_pool_t *p, request_rec *r, X509 *xs,
                                     char *var)
{
    char *result;
    BOOL resdup;
    X509_NAME *xsname;
    int nid;

    result = NULL;
    resdup = TRUE;

    if (strcEQ(var, "M_VERSION")) {
        result = apr_psprintf(p, "%lu", X509_get_version(xs)+1);
        resdup = FALSE;
    }
    else if (strcEQ(var, "M_SERIAL")) {
        result = ssl_var_lookup_ssl_cert_serial(p, xs);
    }
    else if (strcEQ(var, "V_START")) {
        result = ssl_var_lookup_ssl_cert_valid(p, X509_get_notBefore(xs));
    }
    else if (strcEQ(var, "V_END")) {
        result = ssl_var_lookup_ssl_cert_valid(p, X509_get_notAfter(xs));
    }
    else if (strcEQ(var, "V_REMAIN")) {
        result = ssl_var_lookup_ssl_cert_remain(p, X509_get_notAfter(xs));
        resdup = FALSE;
    }
    else if (*var && strcEQ(var+1, "_DN")) {
        if (*var == 'S')
            xsname = X509_get_subject_name(xs);
        else if (*var == 'I')
            xsname = X509_get_issuer_name(xs);
        else
            return NULL;
        result = ssl_var_lookup_ssl_cert_dn_oneline(p, r, xsname);
        resdup = FALSE;
    }
    else if (strlen(var) > 5 && strcEQn(var+1, "_DN_", 4)) {
        if (*var == 'S')
            xsname = X509_get_subject_name(xs);
        else if (*var == 'I')
            xsname = X509_get_issuer_name(xs);
        else
            return NULL;
        result = ssl_var_lookup_ssl_cert_dn(p, xsname, var+5);
        resdup = FALSE;
    }
    else if (strcEQ(var, "A_SIG")) {
        nid = OBJ_obj2nid((ASN1_OBJECT *)(xs->cert_info->signature->algorithm));
        result = apr_pstrdup(p,
                             (nid == NID_undef) ? "UNKNOWN" : OBJ_nid2ln(nid));
        resdup = FALSE;
    }
    else if (strcEQ(var, "A_KEY")) {
        nid = OBJ_obj2nid((ASN1_OBJECT *)(xs->cert_info->key->algor->algorithm));
        result = apr_pstrdup(p,
                             (nid == NID_undef) ? "UNKNOWN" : OBJ_nid2ln(nid));
        resdup = FALSE;
    }
    else if (strcEQ(var, "CERT")) {
        result = ssl_var_lookup_ssl_cert_PEM(p, xs);
    }

    if (resdup)
        result = apr_pstrdup(p, result);
    return result;
}
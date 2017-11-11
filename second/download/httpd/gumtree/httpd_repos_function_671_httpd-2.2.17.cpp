BOOL SSL_X509_getBC(X509 *cert, int *ca, int *pathlen)
{
#ifdef HAVE_SSL_X509V3_EXT_d2i
    X509_EXTENSION *ext;
    BASIC_CONSTRAINTS *bc;
    int idx;
    BIGNUM *bn = NULL;
    char *cp;

    if ((idx = X509_get_ext_by_NID(cert, NID_basic_constraints, -1)) < 0)
        return FALSE;
    ext = X509_get_ext(cert, idx);
    if (ext == NULL)
        return FALSE;
    if ((bc = (BASIC_CONSTRAINTS *)X509V3_EXT_d2i(ext)) == NULL)
        return FALSE;
    *ca = bc->ca;
    *pathlen = -1 /* unlimited */;
    if (bc->pathlen != NULL) {
        if ((bn = ASN1_INTEGER_to_BN(bc->pathlen, NULL)) == NULL)
            return FALSE;
        if ((cp = BN_bn2dec(bn)) == NULL)
            return FALSE;
        *pathlen = atoi(cp);
        free(cp);
        BN_free(bn);
    }
    BASIC_CONSTRAINTS_free(bc);
    return TRUE;
#else
    return FALSE;
#endif
}
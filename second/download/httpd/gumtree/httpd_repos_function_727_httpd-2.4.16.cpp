BOOL SSL_X509_getBC(X509 *cert, int *ca, int *pathlen)
{
    BASIC_CONSTRAINTS *bc;
    BIGNUM *bn = NULL;
    char *cp;

    bc = X509_get_ext_d2i(cert, NID_basic_constraints, NULL, NULL);
    if (bc == NULL)
        return FALSE;
    *ca = bc->ca;
    *pathlen = -1 /* unlimited */;
    if (bc->pathlen != NULL) {
        if ((bn = ASN1_INTEGER_to_BN(bc->pathlen, NULL)) == NULL) {
            BASIC_CONSTRAINTS_free(bc);
            return FALSE;
        }
        if ((cp = BN_bn2dec(bn)) == NULL) {
            BN_free(bn);
            BASIC_CONSTRAINTS_free(bc);
            return FALSE;
        }
        *pathlen = atoi(cp);
        OPENSSL_free(cp);
        BN_free(bn);
    }
    BASIC_CONSTRAINTS_free(bc);
    return TRUE;
}
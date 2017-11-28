static int berEncodeLoginData(
    struct berval **requestBV,
    char     *objectDN,
    unsigned int  methodIDLen,
    unsigned int *methodID,
    char     *tag,
    size_t   putDataLen,
    void     *putData)
{
    int err = 0;
    BerElement *requestBer = NULL;

    unsigned int i;
    unsigned int elemCnt = methodIDLen / sizeof(unsigned int);

    char	*utf8ObjPtr=NULL;
    int     utf8ObjSize = 0;

    char    *utf8TagPtr = NULL;
    int     utf8TagSize = 0;

    utf8ObjPtr = objectDN;
    utf8ObjSize = strlen(utf8ObjPtr)+1;

    utf8TagPtr = tag;
    utf8TagSize = strlen(utf8TagPtr)+1;

    /* Allocate a BerElement for the request parameters. */
    if ((requestBer = ber_alloc()) == NULL) {
        err = LDAP_ENCODING_ERROR;
        goto Cleanup;
    }

    /* BER encode the NMAS Version and the objectDN */
    err = (ber_printf(requestBer, "{io", NMAS_LDAP_EXT_VERSION, utf8ObjPtr, utf8ObjSize) < 0) ? LDAP_ENCODING_ERROR : 0;

    /* BER encode the MethodID Length and value */
    if (!err) {
        err = (ber_printf(requestBer, "{i{", methodIDLen) < 0) ? LDAP_ENCODING_ERROR : 0;
    }

    for (i = 0; !err && i < elemCnt; i++) {
        err = (ber_printf(requestBer, "i", methodID[i]) < 0) ? LDAP_ENCODING_ERROR : 0;
    }

    if (!err) {
        err = (ber_printf(requestBer, "}}", 0) < 0) ? LDAP_ENCODING_ERROR : 0;
    }

    if (putData) {
        /* BER Encode the the tag and data */
        err = (ber_printf(requestBer, "oio}", utf8TagPtr, utf8TagSize, putDataLen, putData, putDataLen) < 0) ? LDAP_ENCODING_ERROR : 0;
    } else {
        /* BER Encode the the tag */
        err = (ber_printf(requestBer, "o}", utf8TagPtr, utf8TagSize) < 0) ? LDAP_ENCODING_ERROR : 0;
    }

    if (err) {
        goto Cleanup;
    }

    /* Convert the BER we just built to a berval that we'll send with the extended request. */
    if (ber_flatten(requestBer, requestBV) == LBER_ERROR) {
        err = LDAP_ENCODING_ERROR;
        goto Cleanup;
    }

Cleanup:

    if (requestBer) {
        ber_free(requestBer, 1);
    }

    return err;
}
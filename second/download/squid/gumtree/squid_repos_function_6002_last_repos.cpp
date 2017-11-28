static int berEncodeLoginData(
    struct berval **requestBV,
    char     *objectDN,
    unsigned int  methodIDLen,
    unsigned int *methodID,
    char     *tag,
    size_t   putDataLen,
    void     *putData)
{
    unsigned int elemCnt = methodIDLen / sizeof(unsigned int);

    char    *utf8ObjPtr=NULL;
    int     utf8ObjSize = 0;

    char    *utf8TagPtr = NULL;
    int     utf8TagSize = 0;

    utf8ObjPtr = objectDN;
    utf8ObjSize = strlen(utf8ObjPtr)+1;

    utf8TagPtr = tag;
    utf8TagSize = strlen(utf8TagPtr)+1;

    /* Allocate a BerElement for the request parameters. */
    BerElement *requestBer = ber_alloc();
    if (!requestBer)
        return LDAP_ENCODING_ERROR;

    /* BER encode the NMAS Version and the objectDN */
    if (ber_printf(requestBer, "{io", NMAS_LDAP_EXT_VERSION, utf8ObjPtr, utf8ObjSize) < 0) {
        ber_free(requestBer, 1);
        return LDAP_ENCODING_ERROR;
    }

    /* BER encode the MethodID Length and value */
    if (ber_printf(requestBer, "{i{", methodIDLen) < 0) {
        ber_free(requestBer, 1);
        return LDAP_ENCODING_ERROR;
    }

    for (unsigned int i = 0; i < elemCnt; ++i) {
        if (ber_printf(requestBer, "i", methodID[i]) < 0) {
            ber_free(requestBer, 1);
            return LDAP_ENCODING_ERROR;
        }
    }

    if (ber_printf(requestBer, "}}", 0) < 0) {
        ber_free(requestBer, 1);
        return LDAP_ENCODING_ERROR;
    }

    if (putData) {
        /* BER Encode the the tag and data */
        if (ber_printf(requestBer, "oio}", utf8TagPtr, utf8TagSize, putDataLen, putData, putDataLen) < 0) {
            ber_free(requestBer, 1);
            return LDAP_ENCODING_ERROR;
        }
    } else {
        /* BER Encode the the tag */
        if (ber_printf(requestBer, "o}", utf8TagPtr, utf8TagSize) < 0) {
            ber_free(requestBer, 1);
            return LDAP_ENCODING_ERROR;
        }
    }

    /* Convert the BER we just built to a berval that we'll send with the extended request. */
    if (static_cast<ber_tag_t>(ber_flatten(requestBer, requestBV)) == LBER_ERROR) {
        ber_free(requestBer, 1);
        return LDAP_ENCODING_ERROR;
    }

    ber_free(requestBer, 1);
    return 0; /* no error */
}
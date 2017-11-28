static int berEncodePasswordData(
    struct berval **requestBV,
    const char    *objectDN,
    const char    *password,
    const char    *password2)
{
    int err = 0, rc=0;
    BerElement *requestBer = NULL;

    const char    * utf8ObjPtr = NULL;
    int     utf8ObjSize = 0;
    const char    * utf8PwdPtr = NULL;
    int     utf8PwdSize = 0;
    const char    * utf8Pwd2Ptr = NULL;
    int     utf8Pwd2Size = 0;

    /* Convert objectDN and tag strings from Unicode to UTF-8 */
    utf8ObjSize = strlen(objectDN)+1;
    utf8ObjPtr = objectDN;

    if (password != NULL) {
        utf8PwdSize = strlen(password)+1;
        utf8PwdPtr = password;
    }

    if (password2 != NULL) {
        utf8Pwd2Size = strlen(password2)+1;
        utf8Pwd2Ptr = password2;
    }

    /* Allocate a BerElement for the request parameters. */
    if ((requestBer = ber_alloc()) == NULL) {
        err = LDAP_ENCODING_ERROR;
        ber_free(requestBer, 1);
        return err;
    }

    if (password != NULL && password2 != NULL) {
        /* BER encode the NMAS Version, the objectDN, and the password */
        rc = ber_printf(requestBer, "{iooo}", NMAS_LDAP_EXT_VERSION, utf8ObjPtr, utf8ObjSize, utf8PwdPtr, utf8PwdSize, utf8Pwd2Ptr, utf8Pwd2Size);
    } else if (password != NULL) {
        /* BER encode the NMAS Version, the objectDN, and the password */
        rc = ber_printf(requestBer, "{ioo}", NMAS_LDAP_EXT_VERSION, utf8ObjPtr, utf8ObjSize, utf8PwdPtr, utf8PwdSize);
    } else {
        /* BER encode the NMAS Version and the objectDN */
        rc = ber_printf(requestBer, "{io}", NMAS_LDAP_EXT_VERSION, utf8ObjPtr, utf8ObjSize);
    }

    if (rc < 0) {
        err = LDAP_ENCODING_ERROR;
    } else {
        err = 0;
        /* Convert the BER we just built to a berval that we'll send with the extended request. */
        if ((ber_tag_t)ber_flatten(requestBer, requestBV) == LBER_ERROR) {
            err = LDAP_ENCODING_ERROR;
        }
    }

    if (requestBer) {
        ber_free(requestBer, 1);
    }

    return err;
}
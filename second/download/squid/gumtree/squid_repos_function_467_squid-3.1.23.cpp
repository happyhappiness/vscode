static int getLoginConfig(
    LDAP	 *ld,
    char     *objectDN,
    unsigned int  methodIDLen,
    unsigned int *methodID,
    char     *tag,
    size_t   *dataLen,
    void     *data )
{
    int     err = 0;
    struct  berval *requestBV = NULL;
    char    *replyOID = NULL;
    struct  berval *replyBV = NULL;
    int     serverVersion = 0;

    /* Validate unicode parameters. */
    if ((strlen(objectDN) == 0) || ld == NULL) {
        return LDAP_NO_SUCH_ATTRIBUTE;
    }

    err = berEncodeLoginData(&requestBV, objectDN, methodIDLen, methodID, tag, 0, NULL);
    if (err) {
        goto Cleanup;
    }

    /* Call the ldap_extended_operation (synchronously) */
    if ((err = ldap_extended_operation_s(ld, NMASLDAP_GET_LOGIN_CONFIG_REQUEST,
                                         requestBV, NULL, NULL, &replyOID, &replyBV))) {
        goto Cleanup;
    }

    /* Make sure there is a return OID */
    if (!replyOID) {
        err = LDAP_NOT_SUPPORTED;
        goto Cleanup;
    }

    /* Is this what we were expecting to get back. */
    if (strcmp(replyOID, NMASLDAP_GET_LOGIN_CONFIG_RESPONSE)) {
        err = LDAP_NOT_SUPPORTED;
        goto Cleanup;
    }

    /* Do we have a good returned berval? */
    if (!replyBV) {
        /* No; returned berval means we experienced a rather drastic error. */
        /* Return operations error. */
        err = LDAP_OPERATIONS_ERROR;
        goto Cleanup;
    }

    err = berDecodeLoginData(replyBV, &serverVersion, dataLen, data);

    if (serverVersion != NMAS_LDAP_EXT_VERSION) {
        err = LDAP_OPERATIONS_ERROR;
        goto Cleanup;
    }

Cleanup:

    if (replyBV) {
        ber_bvfree(replyBV);
    }

    /* Free the return OID string if one was returned. */
    if (replyOID) {
        ldap_memfree(replyOID);
    }

    /* Free memory allocated while building the request ber and berval. */
    if (requestBV) {
        ber_bvfree(requestBV);
    }

    /* Return the appropriate error/success code. */
    return err;
}
static int nmasldap_get_password(
    LDAP     *ld,
    char     *objectDN,
    size_t   *pwdSize,  /* in bytes */
    unsigned char     *pwd )
{
    int err = 0;

    struct berval *requestBV = NULL;
    char *replyOID = NULL;
    struct berval *replyBV = NULL;
    int serverVersion;
    char *pwdBuf;
    size_t pwdBufLen, bufferLen;

    /* Validate char parameters. */
    if (objectDN == NULL || (strlen(objectDN) == 0) || pwdSize == NULL || ld == NULL) {
        return LDAP_NO_SUCH_ATTRIBUTE;
    }

    bufferLen = pwdBufLen = *pwdSize;
    pwdBuf = (char*)SMB_MALLOC_ARRAY(char, pwdBufLen+2);
    if (pwdBuf == NULL) {
        return LDAP_NO_MEMORY;
    }

    err = berEncodePasswordData(&requestBV, objectDN, NULL, NULL);
    if (err) {
        ;
    } else if ((err = ldap_extended_operation_s(ld, NMASLDAP_GET_PASSWORD_REQUEST, requestBV, NULL, NULL, &replyOID, &replyBV))) {
        ; /* Call the ldap_extended_operation (synchronously) */
    } else if (!replyOID) {
        /* Make sure there is a return OID */
        err = LDAP_NOT_SUPPORTED;
    } else if (strcmp(replyOID, NMASLDAP_GET_PASSWORD_RESPONSE)) {
        /* Is this what we were expecting to get back. */
        err = LDAP_NOT_SUPPORTED;
    } else if (!replyBV) {
        /* Do we have a good returned berval? */
        /* No; returned berval means we experienced a rather drastic error. */
        /* Return operations error. */
        err = LDAP_OPERATIONS_ERROR;
    } else {
        err = berDecodeLoginData(replyBV, &serverVersion, &pwdBufLen, pwdBuf);

        if (serverVersion != NMAS_LDAP_EXT_VERSION) {
            err = LDAP_OPERATIONS_ERROR;

        } else if (!err && pwdBufLen != 0) {
            if (*pwdSize >= pwdBufLen+1 && pwd != NULL) {
                memcpy(pwd, pwdBuf, pwdBufLen);
                pwd[pwdBufLen] = 0; /* add null termination */
            }
            *pwdSize = pwdBufLen; /* does not include null termination */
        }
    }

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

    if (pwdBuf != NULL) {
        memset(pwdBuf, 0, bufferLen);
        free(pwdBuf);
    }

    /* Return the appropriate error/success code. */
    return err;
}
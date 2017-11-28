static int nmasldap_get_simple_pwd(
    LDAP	 *ld,
    char     *objectDN,
    size_t	 pwdLen,
    char     *pwd )
{
    int err = 0;
    unsigned int methodID = 0;
    unsigned int methodIDLen = sizeof(methodID);
    char    tag[] = {'P','A','S','S','W','O','R','D',' ','H','A','S','H',0};
    char    *pwdBuf=NULL;
    size_t  pwdBufLen, bufferLen;

    bufferLen = pwdBufLen = pwdLen+2;
    pwdBuf = SMB_MALLOC_ARRAY(char, pwdBufLen); /* digest and null */
    if (pwdBuf == NULL) {
        return LDAP_NO_MEMORY;
    }

    err = getLoginConfig(ld, objectDN, methodIDLen, &methodID, tag, &pwdBufLen, pwdBuf);
    if (err == 0) {
        if (pwdBufLen !=0) {
            pwdBuf[pwdBufLen] = 0;       /* null terminate */

            switch (pwdBuf[0]) {
            case 1:  /* cleartext password  */
                break;
            case 2:  /* SHA1 HASH */
            case 3:  /* MD5_ID */
            case 4:  /* UNIXCrypt_ID */
            case 8:  /* SSHA_ID */
            default: /* Unknown digest */
                err = LDAP_INAPPROPRIATE_AUTH;  /* only return clear text */
                break;
            }

            if (!err) {
                if (pwdLen >= pwdBufLen-1) {
                    memcpy(pwd, &pwdBuf[1], pwdBufLen-1);  /* skip digest tag and include null */
                } else {
                    err = LDAP_NO_MEMORY;
                }
            }
        }
    }

    if (pwdBuf != NULL) {
        memset(pwdBuf, 0, bufferLen);
        free(pwdBuf);
    }

    return err;
}
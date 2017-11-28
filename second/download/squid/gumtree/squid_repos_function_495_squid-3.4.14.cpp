void
LDAPHHA1(RequestData * requestData)
{
    char *password;
    ldapconnect();
    password = getpassword(requestData->user, requestData->realm);
    if (password != NULL) {
        if (encrpass)
            xstrncpy(requestData->HHA1, password, sizeof(requestData->HHA1));
        else {
            HASH HA1;
            DigestCalcHA1("md5", requestData->user, requestData->realm, password, NULL, NULL, HA1, requestData->HHA1);
        }
        free(password);
    } else {
        requestData->error = -1;
    }

}
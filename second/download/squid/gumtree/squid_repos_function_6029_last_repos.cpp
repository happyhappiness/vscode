void
LDAPHHA1(RequestData * requestData)
{
    char *password = NULL;
    ldapconnect();

    // use the -l delimiter to find realm, or
    // only honor the -r specified realm
    const bool lookup = (!*frealm && *delimiter) ||
                        (*frealm && strcmp(requestData->realm, frealm) == 0);

    if (lookup)
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
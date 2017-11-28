const char *
FtpStateData::ftpRealm()
{
    static char realm[8192];

    /* This request is not fully authenticated */
    if (!request) {
        snprintf(realm, 8192, "FTP %s unknown", user);
    } else if (request->port == 21) {
        snprintf(realm, 8192, "FTP %s %s", user, request->GetHost());
    } else {
        snprintf(realm, 8192, "FTP %s %s port %d", user, request->GetHost(), request->port);
    }
    return realm;
}
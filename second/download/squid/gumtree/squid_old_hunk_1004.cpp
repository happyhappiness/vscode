{
    /* default username */
    xstrncpy(user, "anonymous", MAX_URL);

#if HAVE_AUTH_MODULE_BASIC
    /* Check HTTP Authorization: headers (better than defaults, but less than URL) */
    const char *auth;
    if ( (auth = req_hdr->getAuth(HDR_AUTHORIZATION, "Basic")) ) {
        flags.authenticated = 1;
        loginParser(auth, FTP_LOGIN_NOT_ESCAPED);
    }
    /* we fail with authorization-required error later IFF the FTP server requests it */
#endif

    /* Test URL login syntax. Overrides any headers received. */
    loginParser(request->login, FTP_LOGIN_ESCAPED);

    /* name is missing. thats fatal. */
    if (!user[0])
        fatal("FTP login parsing destroyed username info");

    /* name + password == success */

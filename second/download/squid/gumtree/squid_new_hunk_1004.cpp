{
    /* default username */
    xstrncpy(user, "anonymous", MAX_URL);

#if HAVE_AUTH_MODULE_BASIC
    /* Check HTTP Authorization: headers (better than defaults, but less than URL) */
    const SBuf auth(req_hdr->getAuth(Http::HdrType::AUTHORIZATION, "Basic"));
    if (!auth.isEmpty()) {
        flags.authenticated = 1;
        loginParser(auth, false);
    }
    /* we fail with authorization-required error later IFF the FTP server requests it */
#endif

    /* Test URL login syntax. Overrides any headers received. */
    loginParser(request->url.userInfo(), true);

    /* name is missing. thats fatal. */
    if (!user[0])
        fatal("FTP login parsing destroyed username info");

    /* name + password == success */

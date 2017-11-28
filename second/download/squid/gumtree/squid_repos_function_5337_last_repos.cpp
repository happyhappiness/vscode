int
Ftp::Gateway::checkAuth(const HttpHeader * req_hdr)
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
    if (password[0])
        return 1;

    /* Setup default FTP password settings */
    /* this has to be done last so that we can have a no-password case above. */
    if (!password[0]) {
        if (strcmp(user, "anonymous") == 0 && !flags.tried_auth_anonymous) {
            xstrncpy(password, Config.Ftp.anon_user, MAX_URL);
            flags.tried_auth_anonymous=1;
            return 1;
        } else if (!flags.tried_auth_nopass) {
            xstrncpy(password, null_string, MAX_URL);
            flags.tried_auth_nopass=1;
            return 1;
        }
    }

    return 0;           /* different username */
}
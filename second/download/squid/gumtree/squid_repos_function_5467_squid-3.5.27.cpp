void
Ftp::Gateway::loginParser(const char *login, int escaped)
{
    const char *u = NULL; // end of the username sub-string
    int len;              // length of the current sub-string to handle.

    int total_len = strlen(login);

    debugs(9, 4, HERE << ": login='" << login << "', escaped=" << escaped);
    debugs(9, 9, HERE << ": IN : login='" << login << "', escaped=" << escaped << ", user=" << user << ", password=" << password);

    if ((u = strchr(login, ':'))) {

        /* if there was a username part */
        if (u > login) {
            len = u - login;
            ++u; // jump off the delimiter.
            if (len > MAX_URL)
                len = MAX_URL-1;
            xstrncpy(user, login, len +1);
            debugs(9, 9, HERE << ": found user='" << user << "'(" << len <<"), escaped=" << escaped);
            if (escaped)
                rfc1738_unescape(user);
            debugs(9, 9, HERE << ": found user='" << user << "'(" << len <<") unescaped.");
        }

        /* if there was a password part */
        len = login + total_len - u;
        if ( len > 0) {
            if (len > MAX_URL)
                len = MAX_URL -1;
            xstrncpy(password, u, len +1);
            debugs(9, 9, HERE << ": found password='" << password << "'(" << len <<"), escaped=" << escaped);
            if (escaped) {
                rfc1738_unescape(password);
                password_url = 1;
            }
            debugs(9, 9, HERE << ": found password='" << password << "'(" << len <<") unescaped.");
        }
    } else if (login[0]) {
        /* no password, just username */
        if (total_len > MAX_URL)
            total_len = MAX_URL -1;
        xstrncpy(user, login, total_len +1);
        debugs(9, 9, HERE << ": found user='" << user << "'(" << total_len <<"), escaped=" << escaped);
        if (escaped)
            rfc1738_unescape(user);
        debugs(9, 9, HERE << ": found user='" << user << "'(" << total_len <<") unescaped.");
    }

    debugs(9, 9, HERE << ": OUT: login='" << login << "', escaped=" << escaped << ", user=" << user << ", password=" << password);
}
void
Ftp::Gateway::loginParser(const SBuf &login, bool escaped)
{
    debugs(9, 4, "login=" << login << ", escaped=" << escaped);
    debugs(9, 9, "IN : login=" << login << ", escaped=" << escaped << ", user=" << user << ", password=" << password);

    if (login.isEmpty())
        return;

    const SBuf::size_type colonPos = login.find(':');

    /* If there was a username part with at least one character use it.
     * Ignore 0-length username portion, retain what we have already.
     */
    if (colonPos == SBuf::npos || colonPos > 0) {
        const SBuf userName = login.substr(0, colonPos);
        SBuf::size_type upto = userName.copy(user, sizeof(user)-1);
        user[upto]='\0';
        debugs(9, 9, "found user=" << userName << ' ' <<
               (upto != userName.length() ? ", truncated-to=" : ", length=") << upto <<
               ", escaped=" << escaped);
        if (escaped)
            rfc1738_unescape(user);
        debugs(9, 9, "found user=" << user << " (" << strlen(user) << ") unescaped.");
    }

    /* If there was a password part.
     * For 0-length password clobber what we have already, this means explicitly none
     */
    if (colonPos != SBuf::npos) {
        const SBuf pass = login.substr(colonPos+1, SBuf::npos);
        SBuf::size_type upto = pass.copy(password, sizeof(password)-1);
        password[upto]='\0';
        debugs(9, 9, "found password=" << pass << " " <<
               (upto != pass.length() ? ", truncated-to=" : ", length=") << upto <<
               ", escaped=" << escaped);
        if (escaped) {
            rfc1738_unescape(password);
            password_url = 1;
        }
        debugs(9, 9, "found password=" << password << " (" << strlen(password) << ") unescaped.");
    }

    debugs(9, 9, "OUT: login=" << login << ", escaped=" << escaped << ", user=" << user << ", password=" << password);
}
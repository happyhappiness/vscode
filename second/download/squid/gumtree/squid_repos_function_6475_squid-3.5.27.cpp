void
Snmp::Session::assign(const Session& session)
{
    memcpy(this, &session, sizeof(*this));
    if (session.community != NULL) {
        community = (u_char*)xstrdup((char*)session.community);
        Must(community != NULL);
    }
    if (session.peername != NULL) {
        peername = xstrdup(session.peername);
        Must(peername != NULL);
    }
}
void
ExternalACLEntry::update(ExternalACLEntryData const &someData)
{
    date = squid_curtime;
    result = someData.result;

    user = someData.user;
    password = someData.password;
    message = someData.message;
    tag = someData.tag;
    log = someData.log;
}
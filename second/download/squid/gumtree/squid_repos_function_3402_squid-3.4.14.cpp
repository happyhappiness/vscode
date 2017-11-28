void
ExternalACLEntry::update(ExternalACLEntryData const &someData)
{
    date = squid_curtime;
    result = someData.result;

    // replace all notes. not combine
    notes.entries.clean();
    notes.append(&someData.notes);

#if USE_AUTH
    user = someData.user;
    password = someData.password;
#endif
    message = someData.message;
    tag = someData.tag;
    log = someData.log;
}
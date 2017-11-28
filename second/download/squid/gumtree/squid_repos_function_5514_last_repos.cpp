void
IdentLookup::LookupDone(const char *ident, void *data)
{
    ACLFilledChecklist *checklist = Filled(static_cast<ACLChecklist*>(data));

    if (ident) {
        xstrncpy(checklist->rfc931, ident, USER_IDENT_SZ);
    } else {
        xstrncpy(checklist->rfc931, dash_str, USER_IDENT_SZ);
    }

    /*
     * Cache the ident result in the connection, to avoid redoing ident lookup
     * over and over on persistent connections
     */
    if (checklist->conn() != NULL && checklist->conn()->clientConnection != NULL && !checklist->conn()->clientConnection->rfc931[0])
        xstrncpy(checklist->conn()->clientConnection->rfc931, checklist->rfc931, USER_IDENT_SZ);

    checklist->resumeNonBlockingCheck(IdentLookup::Instance());
}
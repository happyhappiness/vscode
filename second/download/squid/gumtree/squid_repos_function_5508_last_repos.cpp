int
ACLIdent::match(ACLChecklist *cl)
{
    ACLFilledChecklist *checklist = Filled(cl);
    if (checklist->rfc931[0]) {
        return data->match(checklist->rfc931);
    } else if (checklist->conn() != NULL && checklist->conn()->clientConnection != NULL && checklist->conn()->clientConnection->rfc931[0]) {
        return data->match(checklist->conn()->clientConnection->rfc931);
    } else if (checklist->conn() != NULL && Comm::IsConnOpen(checklist->conn()->clientConnection)) {
        if (checklist->goAsync(IdentLookup::Instance())) {
            debugs(28, 3, "switching to ident lookup state");
            return -1;
        }
        // else fall through to ACCESS_DUNNO failure below
    } else {
        debugs(28, DBG_IMPORTANT, HERE << "Can't start ident lookup. No client connection" );
        // fall through to ACCESS_DUNNO failure below
    }

    checklist->markFinished(ACCESS_DUNNO, "cannot start ident lookup");
    return -1;
}
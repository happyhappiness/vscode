int
ACLIdent::match(ACLChecklist *cl)
{
    ACLFilledChecklist *checklist = Filled(cl);
    if (checklist->rfc931[0]) {
        return data->match(checklist->rfc931);
    } else if (checklist->conn() != NULL && checklist->conn()->clientConnection != NULL && checklist->conn()->clientConnection->rfc931[0]) {
        return data->match(checklist->conn()->clientConnection->rfc931);
    } else if (checklist->conn() != NULL && Comm::IsConnOpen(checklist->conn()->clientConnection)) {
        debugs(28, 3, HERE << "switching to ident lookup state");
        checklist->changeState(IdentLookup::Instance());
        return 0;
    } else {
        debugs(28, DBG_IMPORTANT, HERE << "Can't start ident lookup. No client connection" );
        checklist->markFinished(ACCESS_DUNNO, "cannot start ident lookup");
        return -1;
    }
}
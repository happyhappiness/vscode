void
IdentLookup::checkForAsync(ACLChecklist *cl)const
{
    ACLFilledChecklist *checklist = Filled(cl);
    const ConnStateData *conn = checklist->conn();
    // check that ACLIdent::match() tested this lookup precondition
    assert(conn && Comm::IsConnOpen(conn->clientConnection));
    debugs(28, 3, HERE << "Doing ident lookup" );
    checklist->asyncInProgress(true);
    Ident::Start(checklist->conn()->clientConnection, LookupDone, checklist);
}
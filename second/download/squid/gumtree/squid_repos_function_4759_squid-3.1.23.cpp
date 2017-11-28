void
IdentLookup::checkForAsync(ACLChecklist *cl)const
{
    ACLFilledChecklist *checklist = Filled(cl);
    if (checklist->conn() != NULL) {
        debugs(28, 3, HERE << "Doing ident lookup" );
        checklist->asyncInProgress(true);
        Ident::Start(checklist->conn()->me, checklist->conn()->peer, LookupDone, checklist);
    } else {
        debugs(28, DBG_IMPORTANT, "IdentLookup::checkForAsync: Can't start ident lookup. No client connection" );
        checklist->currentAnswer(ACCESS_DENIED);
        checklist->markFinished();
    }
}
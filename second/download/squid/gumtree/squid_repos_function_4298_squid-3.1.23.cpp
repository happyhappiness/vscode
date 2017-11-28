void
DestinationIPLookup::checkForAsync(ACLChecklist *cl)const
{
    ACLFilledChecklist *checklist = Filled(cl);
    checklist->asyncInProgress(true);
    ipcache_nbgethostbyname(checklist->request->GetHost(), LookupDone, checklist);
}
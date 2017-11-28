void
DestinationIPLookup::checkForAsync(ACLChecklist *cl)const
{
    ACLFilledChecklist *checklist = Filled(cl);
    ipcache_nbgethostbyname(checklist->request->url.host(), LookupDone, checklist);
}
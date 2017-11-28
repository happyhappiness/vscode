void
DestinationIPLookup::LookupDone(const ipcache_addrs *, const Dns::LookupDetails &details, void *data)
{
    ACLFilledChecklist *checklist = Filled((ACLChecklist*)data);
    checklist->request->flags.destinationIpLookedUp = true;
    checklist->request->recordLookup(details);
    checklist->resumeNonBlockingCheck(DestinationIPLookup::Instance());
}
void
DestinationDomainLookup::checkForAsync(ACLChecklist *cl) const
{
    ACLFilledChecklist *checklist = Filled(cl);
    checklist->asyncInProgress(true);
    fqdncache_nbgethostbyaddr(checklist->dst_addr, LookupDone, checklist);
}
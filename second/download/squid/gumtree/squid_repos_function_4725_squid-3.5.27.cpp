void
DestinationDomainLookup::checkForAsync(ACLChecklist *cl) const
{
    ACLFilledChecklist *checklist = Filled(cl);
    fqdncache_nbgethostbyaddr(checklist->dst_addr, LookupDone, checklist);
}
void
SourceDomainLookup::checkForAsync(ACLChecklist *checklist) const
{
    checklist->asyncInProgress(true);
    fqdncache_nbgethostbyaddr(Filled(checklist)->src_addr, LookupDone, checklist);
}
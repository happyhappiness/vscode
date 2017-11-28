void
SourceDomainLookup::checkForAsync(ACLChecklist *checklist) const
{
    fqdncache_nbgethostbyaddr(Filled(checklist)->src_addr, LookupDone, checklist);
}
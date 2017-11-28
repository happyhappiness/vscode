void
DestinationDomainLookup::LookupDone(const char *fqdn, const DnsLookupDetails &details, void *data)
{
    ACLFilledChecklist *checklist = Filled((ACLChecklist*)data);
    checklist->markDestinationDomainChecked();
    checklist->request->recordLookup(details);
    checklist->resumeNonBlockingCheck(DestinationDomainLookup::Instance());
}
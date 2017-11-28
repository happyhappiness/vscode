void
SourceDomainLookup::LookupDone(const char *fqdn, const DnsLookupDetails &details, void *data)
{
    ACLFilledChecklist *checklist = Filled((ACLChecklist*)data);
    checklist->markSourceDomainChecked();
    checklist->request->recordLookup(details);
    checklist->resumeNonBlockingCheck(SourceDomainLookup::Instance());
}
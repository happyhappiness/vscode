void
SourceDomainLookup::LookupDone(const char *, const Dns::LookupDetails &details, void *data)
{
    ACLFilledChecklist *checklist = Filled((ACLChecklist*)data);
    checklist->markSourceDomainChecked();
    checklist->request->recordLookup(details);
    checklist->resumeNonBlockingCheck(SourceDomainLookup::Instance());
}
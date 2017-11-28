void
SourceDomainLookup::LookupDone(const char *fqdn, const DnsLookupDetails &details, void *data)
{
    ACLFilledChecklist *checklist = Filled((ACLChecklist*)data);
    assert (checklist->asyncState() == SourceDomainLookup::Instance());

    checklist->asyncInProgress(false);
    checklist->changeState (ACLChecklist::NullState::Instance());
    checklist->markSourceDomainChecked();
    checklist->request->recordLookup(details);
    checklist->check();
}
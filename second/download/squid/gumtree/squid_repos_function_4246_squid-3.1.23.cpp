void
DestinationDomainLookup::LookupDone(const char *fqdn, const DnsLookupDetails &details, void *data)
{
    ACLFilledChecklist *checklist = Filled((ACLChecklist*)data);
    assert (checklist->asyncState() == DestinationDomainLookup::Instance());

    checklist->asyncInProgress(false);
    checklist->changeState (ACLChecklist::NullState::Instance());
    checklist->markDestinationDomainChecked();
    checklist->request->recordLookup(details);
    checklist->check();
}
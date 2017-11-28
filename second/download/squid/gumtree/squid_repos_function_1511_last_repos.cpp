void
ExternalACLLookup::LookupDone(void *data, const ExternalACLEntryPointer &result)
{
    ACLFilledChecklist *checklist = Filled(static_cast<ACLChecklist*>(data));
    checklist->extacl_entry = result;
    checklist->resumeNonBlockingCheck(ExternalACLLookup::Instance());
}
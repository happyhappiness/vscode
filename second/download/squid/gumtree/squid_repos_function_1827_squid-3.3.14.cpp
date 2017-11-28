void
ExternalACLLookup::LookupDone(void *data, void *result)
{
    ACLFilledChecklist *checklist = Filled(static_cast<ACLChecklist*>(data));
    checklist->extacl_entry = cbdataReference((external_acl_entry *)result);
    checklist->asyncInProgress(false);
    checklist->changeState (ACLChecklist::NullState::Instance());
    checklist->matchNonBlocking();
}
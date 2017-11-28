void
ACLExternal::ExternalAclLookup(ACLChecklist *checklist, ACLExternal * me)
{
    ExternalACLLookup::Start(checklist, me->data, false);
}
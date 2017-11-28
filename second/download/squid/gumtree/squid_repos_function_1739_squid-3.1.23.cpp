int
ACLExternal::match(ACLChecklist *checklist)
{
    return aclMatchExternal (data, Filled(checklist));
}
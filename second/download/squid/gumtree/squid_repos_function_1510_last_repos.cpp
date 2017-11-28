void
ExternalACLLookup::checkForAsync(ACLChecklist *checklist)const
{
    /* TODO: optimise this - we probably have a pointer to this
     * around somewhere */
    ACL *acl = ACL::FindByName(AclMatchedName);
    assert(acl);
    ACLExternal *me = dynamic_cast<ACLExternal *> (acl);
    assert (me);
    ACLExternal::ExternalAclLookup(checklist, me);
}
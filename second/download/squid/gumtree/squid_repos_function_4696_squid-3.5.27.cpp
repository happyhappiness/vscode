void
aclDestroyAcls(ACL ** head)
{
    *head = NULL; // Config.aclList
    if (AclSet *acls = RegisteredAcls) {
        debugs(28, 8, "deleting all " << acls->size() << " ACLs");
        while (!acls->empty()) {
            ACL *acl = *acls->begin();
            // We use centralized deletion (this function) so ~ACL should not
            // delete other ACLs, but we still deregister first to prevent any
            // accesses to the being-deleted ACL via RegisteredAcls.
            assert(acl->registered); // make sure we are making progress
            aclDeregister(acl);
            delete acl;
        }
    }
}
static void
freed_acl_address(void *data)
{
    AclAddress *l = static_cast<AclAddress *>(data);
    aclDestroyAclList(&l->aclList);
}
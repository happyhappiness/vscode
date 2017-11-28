static void
freed_acl_address(void *data)
{
    acl_address *l = static_cast<acl_address *>(data);
    aclDestroyAclList(&l->aclList);
}
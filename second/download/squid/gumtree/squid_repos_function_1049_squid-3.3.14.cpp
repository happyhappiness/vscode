static void
freed_acl_nfmark(void *data)
{
    acl_nfmark *l = static_cast<acl_nfmark *>(data);
    aclDestroyAclList(&l->aclList);
}
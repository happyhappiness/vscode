static void
freed_acl_b_size_t(void *data)
{
    AclSizeLimit *l = static_cast<AclSizeLimit *>(data);
    aclDestroyAclList(&l->aclList);
}
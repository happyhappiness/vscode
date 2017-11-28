static void
freed_acl_b_size_t(void *data)
{
    acl_size_t *l = static_cast<acl_size_t *>(data);
    aclDestroyAclList(&l->aclList);
}
static void
freed_acl_tos(void *data)
{
    acl_tos *l = static_cast<acl_tos *>(data);
    aclDestroyAclList(&l->aclList);
}
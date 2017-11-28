static void
free_external_acl_format(void *data)
{
    external_acl_format *p = static_cast<external_acl_format *>(data);
    safe_free(p->header);
}
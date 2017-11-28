void
free_externalAclHelper(external_acl ** list)
{
    delete *list;
    *list = NULL;
}
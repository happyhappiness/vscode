void
free_externalAclHelper(external_acl ** list)
{
    while (*list) {
        external_acl *node = *list;
        *list = node->next;
        node->next = NULL;
        cbdataFree(node);
    }
}
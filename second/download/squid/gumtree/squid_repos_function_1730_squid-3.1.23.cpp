static external_acl *
find_externalAclHelper(const char *name)
{
    external_acl *node;

    for (node = Config.externalAclHelperList; node; node = node->next) {
        if (strcmp(node->name, name) == 0)
            return node;
    }

    return NULL;
}
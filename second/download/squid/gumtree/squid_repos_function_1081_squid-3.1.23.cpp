void
free_denyinfo(acl_deny_info_list ** list)
{
    acl_deny_info_list *a = NULL;
    acl_deny_info_list *a_next = NULL;
    acl_name_list *l = NULL;
    acl_name_list *l_next = NULL;

    for (a = *list; a; a = a_next) {
        for (l = a->acl_list; l; l = l_next) {
            l_next = l->next;
            memFree(l, MEM_ACL_NAME_LIST);
            l = NULL;
        }

        a_next = a->next;
        memFree(a, MEM_ACL_DENY_INFO_LIST);
        a = NULL;
    }

    *list = NULL;
}
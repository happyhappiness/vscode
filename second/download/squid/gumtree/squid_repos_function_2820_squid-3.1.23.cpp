void
wccp2_add_service_list(int service, int service_id, int service_priority,
                       int service_proto, int service_flags, int ports[], int security_type,
                       char *password)
{

    struct wccp2_service_list_t *wccp2_service_list_ptr;

    wccp2_service_list_ptr = (wccp2_service_list_t *) xcalloc(1, sizeof(struct wccp2_service_list_t));

    debugs(80, 5, "wccp2_add_service_list: added service id " << service_id);

    /* XXX check what needs to be wrapped in htons()! */
    wccp2_service_list_ptr->info.service_type = htons(WCCP2_SERVICE_INFO);

    wccp2_service_list_ptr->info.service_length = htons(sizeof(struct wccp2_service_info_t) - 4);
    wccp2_service_list_ptr->change_num = 0;
    wccp2_update_service(wccp2_service_list_ptr, service, service_id,
                         service_priority, service_proto, service_flags, ports);
    wccp2_service_list_ptr->wccp2_security_type = security_type;
    memset(wccp2_service_list_ptr->wccp_password, 0, WCCP2_PASSWORD_LEN + 1);
    strncpy(wccp2_service_list_ptr->wccp_password, password, WCCP2_PASSWORD_LEN);
    /* add to linked list - XXX this should use the Squid dlink* routines! */
    wccp2_service_list_ptr->next = wccp2_service_list_head;
    wccp2_service_list_head = wccp2_service_list_ptr;
}
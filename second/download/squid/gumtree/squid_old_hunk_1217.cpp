
    /* Create a placeholder service record */
    wccp2_add_service_list(service, service_id, 0, 0, 0, empty_portlist, security_type, wccp_password);
}

void
dump_wccp2_service(StoreEntry * e, const char *label, void *v)
{

    struct wccp2_service_list_t *srv;
    srv = wccp2_service_list_head;

    while (srv != NULL) {
        debugs(80, 3, "dump_wccp2_service: id " << srv->info.service_id << ", type " << srv->info.service);
        storeAppendPrintf(e, "%s %s %d", label,

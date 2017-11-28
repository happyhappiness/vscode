void
dump_wccp2_service(StoreEntry * e, const char *label, void *)
{
    struct wccp2_service_list_t *srv;
    srv = wccp2_service_list_head;

    while (srv != NULL) {
        debugs(80, 3, "dump_wccp2_service: id " << srv->info.service_id << ", type " << srv->info.service);
        storeAppendPrintf(e, "%s %s %d", label,
                          (srv->info.service == WCCP2_SERVICE_DYNAMIC) ? "dynamic" : "standard",
                          srv->info.service_id);

        if (srv->wccp2_security_type == WCCP2_MD5_SECURITY) {
            storeAppendPrintf(e, " %s", srv->wccp_password);
        }

        storeAppendPrintf(e, "\n");

        srv = srv->next;
    }
}
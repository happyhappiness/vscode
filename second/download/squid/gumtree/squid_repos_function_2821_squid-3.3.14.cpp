void
wccp2ConnectionClose(void)
{

    struct wccp2_service_list_t *service_list_ptr;

    struct wccp2_service_list_t *service_list_ptr_next;

    struct wccp2_router_list_t *router_list_ptr;

    struct wccp2_router_list_t *router_list_next;

    struct wccp2_cache_list_t *cache_list_ptr;

    struct wccp2_cache_list_t *cache_list_ptr_next;

    if (wccp2_connected == 0) {
        return;
    }

    if (theWccp2Connection > -1) {
        debugs(80, DBG_IMPORTANT, "FD " << theWccp2Connection << " Closing WCCPv2 socket");
        comm_close(theWccp2Connection);
        theWccp2Connection = -1;
    }

    /* for each router on each service send a packet */
    service_list_ptr = wccp2_service_list_head;

    while (service_list_ptr != NULL) {
        for (router_list_ptr = &service_list_ptr->router_list_head; router_list_ptr != NULL; router_list_ptr = router_list_next) {
            for (cache_list_ptr = &router_list_ptr->cache_list_head; cache_list_ptr; cache_list_ptr = cache_list_ptr_next) {
                cache_list_ptr_next = cache_list_ptr->next;

                if (cache_list_ptr != &router_list_ptr->cache_list_head) {
                    xfree(cache_list_ptr);
                } else {

                    memset(cache_list_ptr, '\0', sizeof(struct wccp2_cache_list_t));
                }
            }

            router_list_next = router_list_ptr->next;

            if (router_list_ptr != &service_list_ptr->router_list_head) {
                xfree(router_list_ptr);
            } else {

                memset(router_list_ptr, '\0', sizeof(struct wccp2_router_list_t));
            }
        }

        service_list_ptr_next = service_list_ptr->next;
        xfree(service_list_ptr);
        service_list_ptr = service_list_ptr_next;
    }

    wccp2_service_list_head = NULL;
    eventDelete(wccp2HereIam, NULL);
    eventDelete(wccp2AssignBuckets, NULL);
    eventDelete(wccp2HereIam, NULL);
    wccp2_connected = 0;
}
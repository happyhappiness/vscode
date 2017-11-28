static void
wccp2HereIam(void *voidnotused)
{

    struct wccp2_service_list_t *service_list_ptr;

    struct wccp2_router_list_t *router_list_ptr;

    struct wccp2_identity_info_t *wccp2_identity_info_ptr;

    struct wccp2_mask_identity_info_t *wccp2_mask_identity_info_ptr;

    Ip::Address router;

    debugs(80, 6, "wccp2HereIam: Called");

    if (wccp2_connected == 0) {
        debugs(80, DBG_IMPORTANT, "wccp2HereIam: wccp2 socket closed.  Shutting down WCCP2");
        return;
    }

    /* Wait if store dirs are rebuilding */
    if (StoreController::store_dirs_rebuilding && Config.Wccp2.rebuildwait) {
        eventAdd("wccp2HereIam", wccp2HereIam, NULL, 1.0, 1);
        return;
    }

    router.port(WCCP_PORT);

    /* for each router on each service send a packet */
    service_list_ptr = wccp2_service_list_head;

    while (service_list_ptr != NULL) {
        debugs(80, 5, "wccp2HereIam: sending to service id " << service_list_ptr->info.service_id);

        for (router_list_ptr = &service_list_ptr->router_list_head; router_list_ptr->next != NULL; router_list_ptr = router_list_ptr->next) {
            router = router_list_ptr->router_sendto_address;

            /* Set the cache id (ip) */

            switch (Config.Wccp2.assignment_method) {

            case WCCP2_ASSIGNMENT_METHOD_HASH:

                wccp2_identity_info_ptr = (struct wccp2_identity_info_t *) service_list_ptr->wccp2_identity_info_ptr;
                wccp2_identity_info_ptr->cache_identity.addr = router_list_ptr->local_ip;
                break;

            case WCCP2_ASSIGNMENT_METHOD_MASK:

                wccp2_mask_identity_info_ptr = (struct wccp2_mask_identity_info_t *) service_list_ptr->wccp2_identity_info_ptr;
                wccp2_mask_identity_info_ptr->cache_identity.addr = router_list_ptr->local_ip;
                break;

            default:
                fatalf("Unknown Wccp2 assignment method\n");
            }

            /* Security update, if needed */

            if (service_list_ptr->wccp2_security_type == WCCP2_MD5_SECURITY) {
                wccp2_update_md5_security(service_list_ptr->wccp_password, (char *) service_list_ptr->security_info, service_list_ptr->wccp_packet, service_list_ptr->wccp_packet_size);
            }

            debugs(80, 3, "Sending HereIam packet size " << service_list_ptr->wccp_packet_size);
            /* Send the packet */

            if (wccp2_numrouters > 1) {
                comm_udp_sendto(theWccp2Connection,
                                router,
                                &service_list_ptr->wccp_packet,
                                service_list_ptr->wccp_packet_size);
            } else {
                errno = 0;
                if (send(theWccp2Connection, &service_list_ptr->wccp_packet, service_list_ptr->wccp_packet_size, 0) < static_cast<int>(service_list_ptr->wccp_packet_size))
                    debugs(80, 2, "ERROR: failed to send WCCPv2 HERE_I_AM packet to " << router << " : " << xstrerror());
            }
        }

        service_list_ptr = service_list_ptr->next;
    }

    eventAdd("wccp2HereIam", wccp2HereIam, NULL, 10.0, 1);
}
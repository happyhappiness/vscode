void
wccp2Init(void)
{
    Ip::Address_list *s;
    char *ptr;
    uint32_t service_flags;

    struct wccp2_service_list_t *service_list_ptr;

    struct wccp2_router_list_t *router_list_ptr;

    struct wccp2_security_md5_t wccp2_security_md5;

    debugs(80, 5, "wccp2Init: Called");

    if (wccp2_connected == 1)
        return;

    wccp2_numrouters = 0;

    /* Calculate the number of routers configured in the config file */
    for (s = Config.Wccp2.router; s; s = s->next) {
        if (!s->s.IsAnyAddr()) {
            /* Increment the counter */
            ++wccp2_numrouters;
        }
    }

    if (wccp2_numrouters == 0) {
        return;
    }

    /* Initialise the list of services */
    wccp2InitServices();

    service_list_ptr = wccp2_service_list_head;

    while (service_list_ptr != NULL) {
        /* Set up our list pointers */
        router_list_ptr = &service_list_ptr->router_list_head;

        /* start the wccp header */
        wccp2_here_i_am_header.type = htonl(WCCP2_HERE_I_AM);
        wccp2_here_i_am_header.version = htons(WCCP2_VERSION);
        wccp2_here_i_am_header.length = 0;
        ptr = service_list_ptr->wccp_packet + sizeof(wccp2_here_i_am_header);

        /* add the security section */
        /* XXX this is ugly */

        if (service_list_ptr->wccp2_security_type == WCCP2_MD5_SECURITY) {
            wccp2_security_md5.security_option = htonl(WCCP2_MD5_SECURITY);

            wccp2_security_md5.security_length = htons(sizeof(struct wccp2_security_md5_t) - 4);
        } else if (service_list_ptr->wccp2_security_type == WCCP2_NO_SECURITY) {
            wccp2_security_md5.security_option = htonl(WCCP2_NO_SECURITY);
            /* XXX I hate magic length numbers! */
            wccp2_security_md5.security_length = htons(4);
        } else {
            fatalf("Bad WCCP2 security type\n");
        }

        wccp2_here_i_am_header.length += ntohs(wccp2_security_md5.security_length) + 4;
        assert(wccp2_here_i_am_header.length <= WCCP_RESPONSE_SIZE);
        wccp2_security_md5.security_type = htons(WCCP2_SECURITY_INFO);

        service_list_ptr->security_info = (struct wccp2_security_md5_t *) ptr;

        if (service_list_ptr->wccp2_security_type == WCCP2_MD5_SECURITY) {
            memcpy(ptr, &wccp2_security_md5, sizeof(struct wccp2_security_md5_t));
            ptr += sizeof(struct wccp2_security_md5_t);
        } else {
            /* assume NONE, and XXX I hate magic length numbers */
            memcpy(ptr, &wccp2_security_md5, 8);
            ptr += 8;
        }

        /* Add the service info section */

        wccp2_here_i_am_header.length += sizeof(struct wccp2_service_info_t);

        assert(wccp2_here_i_am_header.length <= WCCP_RESPONSE_SIZE);

        memcpy(ptr, &service_list_ptr->info, sizeof(struct wccp2_service_info_t));

        service_list_ptr->service_info = (struct wccp2_service_info_t *) ptr;

        ptr += sizeof(struct wccp2_service_info_t);

        /* Add the cache identity section */

        switch (Config.Wccp2.assignment_method) {

        case WCCP2_ASSIGNMENT_METHOD_HASH:

            wccp2_here_i_am_header.length += sizeof(struct wccp2_identity_info_t);
            assert(wccp2_here_i_am_header.length <= WCCP_RESPONSE_SIZE);
            wccp2_identity_info.cache_identity_type = htons(WCCP2_WC_ID_INFO);
            wccp2_identity_info.cache_identity_length = htons(sizeof(wccp2_identity_info.cache_identity));
            memset(&wccp2_identity_info.cache_identity.addr, '\0', sizeof(struct in_addr));
            memset(&wccp2_identity_info.cache_identity.hash_revision, '\0', sizeof(wccp2_identity_info.cache_identity.hash_revision));
            memset(&wccp2_identity_info.cache_identity.bits, '\0', sizeof(wccp2_identity_info.cache_identity.bits));
            memset(&wccp2_identity_info.cache_identity.buckets, '\0', sizeof(wccp2_identity_info.cache_identity.buckets));
            wccp2_identity_info.cache_identity.weight = htons(Config.Wccp2.weight);
            memset(&wccp2_identity_info.cache_identity.status, '\0', sizeof(wccp2_identity_info.cache_identity.status));

            memcpy(ptr, &wccp2_identity_info, sizeof(struct wccp2_identity_info_t));
            service_list_ptr->wccp2_identity_info_ptr = ptr;

            ptr += sizeof(struct wccp2_identity_info_t);
            break;

        case WCCP2_ASSIGNMENT_METHOD_MASK:

            wccp2_here_i_am_header.length += sizeof(struct wccp2_mask_identity_info_t);
            assert(wccp2_here_i_am_header.length <= WCCP_RESPONSE_SIZE);
            wccp2_mask_identity_info.cache_identity_type = htons(WCCP2_WC_ID_INFO);
            wccp2_mask_identity_info.cache_identity_length = htons(sizeof(wccp2_mask_identity_info.cache_identity));
            memset(&wccp2_mask_identity_info.cache_identity.addr, '\0', sizeof(struct in_addr));
            wccp2_mask_identity_info.cache_identity.bits = htons(WCCP2_MASK_ASSIGNMENT_DATA);
            wccp2_mask_identity_info.cache_identity.mask_element_count = htonl(1);
            service_flags = ntohl(service_list_ptr->service_info->service_flags);

            memset(&wccp2_mask_identity_info.cache_identity.mask, 0, sizeof(struct wccp2_mask_element_t));

            if ((service_flags & WCCP2_SERVICE_SRC_IP_HASH) || (service_flags & WCCP2_SERVICE_SRC_IP_ALT_HASH)) {
                wccp2_mask_identity_info.cache_identity.mask.source_ip_mask = htonl(0x00001741);
            } else if ((service_list_ptr->info.service == WCCP2_SERVICE_STANDARD) || (service_flags & WCCP2_SERVICE_DST_IP_HASH) || (service_flags & WCCP2_SERVICE_DST_IP_ALT_HASH)) {
                wccp2_mask_identity_info.cache_identity.mask.dest_ip_mask = htonl(0x00001741);
            } else if ((service_flags & WCCP2_SERVICE_SRC_PORT_HASH) || (service_flags & WCCP2_SERVICE_SRC_PORT_ALT_HASH)) {
                wccp2_mask_identity_info.cache_identity.mask.source_port_mask = htons(0x1741);
            } else if ((service_flags & WCCP2_SERVICE_DST_PORT_HASH) || (service_flags & WCCP2_SERVICE_DST_PORT_ALT_HASH)) {
                wccp2_mask_identity_info.cache_identity.mask.dest_port_mask = htons(0x1741);
            } else {
                fatalf("Unknown service hash method\n");
            }

            wccp2_mask_identity_info.cache_identity.weight = 0;
            wccp2_mask_identity_info.cache_identity.status = 0;

            memcpy(ptr, &wccp2_mask_identity_info, sizeof(struct wccp2_mask_identity_info_t));
            service_list_ptr->wccp2_identity_info_ptr = ptr;

            ptr += sizeof(struct wccp2_mask_identity_info_t);
            break;

        default:
            fatalf("Unknown Wccp2 assignment method\n");
        }

        /* Add the cache view section */
        wccp2_here_i_am_header.length += sizeof(wccp2_cache_view_header);

        assert(wccp2_here_i_am_header.length <= WCCP_RESPONSE_SIZE);

        wccp2_cache_view_header.cache_view_type = htons(WCCP2_WC_VIEW_INFO);

        wccp2_cache_view_header.cache_view_length = htons(sizeof(wccp2_cache_view_header) - 4 +
                sizeof(wccp2_cache_view_info) + (wccp2_numrouters * sizeof(wccp2_router_id_element)));

        wccp2_cache_view_header.cache_view_version = htonl(1);

        memcpy(ptr, &wccp2_cache_view_header, sizeof(wccp2_cache_view_header));

        ptr += sizeof(wccp2_cache_view_header);

        /* Add the number of routers to the packet */
        wccp2_here_i_am_header.length += sizeof(service_list_ptr->num_routers);

        assert(wccp2_here_i_am_header.length <= WCCP_RESPONSE_SIZE);

        service_list_ptr->num_routers = htonl(wccp2_numrouters);

        memcpy(ptr, &service_list_ptr->num_routers, sizeof(service_list_ptr->num_routers));

        ptr += sizeof(service_list_ptr->num_routers);

        /* Add each router.  Keep this functionality here to make sure the received_id can be updated in the packet */
        for (s = Config.Wccp2.router; s; s = s->next) {
            if (!s->s.IsAnyAddr()) {

                wccp2_here_i_am_header.length += sizeof(struct wccp2_router_id_element_t);
                assert(wccp2_here_i_am_header.length <= WCCP_RESPONSE_SIZE);

                /* Add a pointer to the router list for this router */

                router_list_ptr->info = (struct wccp2_router_id_element_t *) ptr;
                s->s.GetInAddr(router_list_ptr->info->router_address);
                router_list_ptr->info->received_id = htonl(0);
                s->s.GetInAddr(router_list_ptr->router_sendto_address);
                router_list_ptr->member_change = htonl(0);

                /* Build the next struct */

                router_list_ptr->next = (wccp2_router_list_t*) xcalloc(1, sizeof(struct wccp2_router_list_t));

                /* update the pointer */
                router_list_ptr = router_list_ptr->next;
                router_list_ptr->next = NULL;

                /* no need to copy memory - we've just set the values directly in the packet above */

                ptr += sizeof(struct wccp2_router_id_element_t);
            }
        }

        /* Add the number of caches (0) */
        wccp2_here_i_am_header.length += sizeof(wccp2_cache_view_info.num_caches);

        assert(wccp2_here_i_am_header.length <= WCCP_RESPONSE_SIZE);

        wccp2_cache_view_info.num_caches = htonl(0);

        memcpy(ptr, &wccp2_cache_view_info.num_caches, sizeof(wccp2_cache_view_info.num_caches));

        ptr += sizeof(wccp2_cache_view_info.num_caches);

        /* Add the extra capability header */
        wccp2_here_i_am_header.length += sizeof(wccp2_capability_info_header);

        assert(wccp2_here_i_am_header.length <= WCCP_RESPONSE_SIZE);

        wccp2_capability_info_header.capability_info_type = htons(WCCP2_CAPABILITY_INFO);

        wccp2_capability_info_header.capability_info_length = htons(3 * sizeof(wccp2_capability_element));

        memcpy(ptr, &wccp2_capability_info_header, sizeof(wccp2_capability_info_header));

        ptr += sizeof(wccp2_capability_info_header);

        /* Add the forwarding method */
        wccp2_here_i_am_header.length += sizeof(wccp2_capability_element);

        assert(wccp2_here_i_am_header.length <= WCCP_RESPONSE_SIZE);

        wccp2_capability_element.capability_type = htons(WCCP2_CAPABILITY_FORWARDING_METHOD);

        wccp2_capability_element.capability_length = htons(sizeof(wccp2_capability_element.capability_value));

        wccp2_capability_element.capability_value = htonl(Config.Wccp2.forwarding_method);

        memcpy(ptr, &wccp2_capability_element, sizeof(wccp2_capability_element));

        ptr += sizeof(wccp2_capability_element);

        /* Add the assignment method */
        wccp2_here_i_am_header.length += sizeof(wccp2_capability_element);

        assert(wccp2_here_i_am_header.length <= WCCP_RESPONSE_SIZE);

        wccp2_capability_element.capability_type = htons(WCCP2_CAPABILITY_ASSIGNMENT_METHOD);

        wccp2_capability_element.capability_length = htons(sizeof(wccp2_capability_element.capability_value));

        wccp2_capability_element.capability_value = htonl(Config.Wccp2.assignment_method);

        memcpy(ptr, &wccp2_capability_element, sizeof(wccp2_capability_element));

        ptr += sizeof(wccp2_capability_element);

        /* Add the return method */
        wccp2_here_i_am_header.length += sizeof(wccp2_capability_element);

        assert(wccp2_here_i_am_header.length <= WCCP_RESPONSE_SIZE);

        wccp2_capability_element.capability_type = htons(WCCP2_CAPABILITY_RETURN_METHOD);

        wccp2_capability_element.capability_length = htons(sizeof(wccp2_capability_element.capability_value));

        wccp2_capability_element.capability_value = htonl(Config.Wccp2.return_method);

        memcpy(ptr, &wccp2_capability_element, sizeof(wccp2_capability_element));

        ptr += sizeof(wccp2_capability_element);

        /* Finally, fix the total length to network order, and copy to the appropriate memory blob */
        wccp2_here_i_am_header.length = htons(wccp2_here_i_am_header.length);

        memcpy(&service_list_ptr->wccp_packet, &wccp2_here_i_am_header, sizeof(wccp2_here_i_am_header));

        service_list_ptr->wccp_packet_size = ntohs(wccp2_here_i_am_header.length) + sizeof(wccp2_here_i_am_header);

        /* Add the event if everything initialised correctly */
        debugs(80,3,"wccp2Init: scheduled 'HERE_I_AM' message to " << wccp2_numrouters << "routers.");
        if (wccp2_numrouters) {
            if (!eventFind(wccp2HereIam, NULL)) {
                eventAdd("wccp2HereIam", wccp2HereIam, NULL, 1, 1);
            } else
                debugs(80,3,"wccp2Init: skip duplicate 'HERE_I_AM'.");
        }

        service_list_ptr = service_list_ptr->next;
    }
}
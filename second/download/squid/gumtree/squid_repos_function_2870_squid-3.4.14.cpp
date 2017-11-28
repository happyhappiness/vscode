static void
wccp2HandleUdp(int sock, void *not_used)
{

    struct wccp2_service_list_t *service_list_ptr;

    struct wccp2_router_list_t *router_list_ptr;

    struct wccp2_cache_list_t *cache_list_ptr;

    struct wccp2_cache_list_t *cache_list_ptr_next;

    /* These structs form the parts of the packet */

    struct wccp2_item_header_t *header = NULL;

    struct wccp2_security_none_t *security_info = NULL;

    struct wccp2_service_info_t *service_info = NULL;

    struct router_identity_info_t *router_identity_info = NULL;

    struct router_view_t *router_view_header = NULL;

    struct wccp2_cache_mask_identity_info_t *cache_mask_identity = NULL;

    struct cache_mask_info_t *cache_mask_info = NULL;

    struct wccp2_cache_identity_info_t *cache_identity = NULL;

    struct wccp2_capability_info_header_t *router_capability_header = NULL;

    struct wccp2_capability_element_t *router_capability_element;

    struct sockaddr_in from;

    struct in_addr cache_address;
    int len, found;
    short int data_length, offset;
    uint32_t tmp;
    char *ptr;
    int num_caches;

    debugs(80, 6, "wccp2HandleUdp: Called.");

    Comm::SetSelect(sock, COMM_SELECT_READ, wccp2HandleUdp, NULL, 0);

    /* FIXME INET6 : drop conversion boundary */
    Ip::Address from_tmp;
    from_tmp.setIPv4();

    len = comm_udp_recvfrom(sock,
                            &wccp2_i_see_you,
                            WCCP_RESPONSE_SIZE,
                            0,
                            from_tmp);

    if (len < 0)
        return;

    if (ntohs(wccp2_i_see_you.version) != WCCP2_VERSION)
        return;

    if (ntohl(wccp2_i_see_you.type) != WCCP2_I_SEE_YOU)
        return;

    /* FIXME INET6 : drop conversion boundary */
    from_tmp.getSockAddr(from);

    debugs(80, 3, "Incoming WCCPv2 I_SEE_YOU length " << ntohs(wccp2_i_see_you.length) << ".");

    /* Record the total data length */
    data_length = ntohs(wccp2_i_see_you.length);

    offset = 0;

    if (data_length > len) {
        debugs(80, DBG_IMPORTANT, "ERROR: Malformed WCCPv2 packet claiming it's bigger than received data");
        return;
    }

    /* Go through the data structure */
    while (data_length > offset) {

        char *data = wccp2_i_see_you.data;

        header = (struct wccp2_item_header_t *) &data[offset];

        switch (ntohs(header->type)) {

        case WCCP2_SECURITY_INFO:

            if (security_info != NULL) {
                debugs(80, DBG_IMPORTANT, "Duplicate security definition");
                return;
            }

            security_info = (struct wccp2_security_none_t *) &wccp2_i_see_you.data[offset];
            break;

        case WCCP2_SERVICE_INFO:

            if (service_info != NULL) {
                debugs(80, DBG_IMPORTANT, "Duplicate service_info definition");
                return;
            }

            service_info = (struct wccp2_service_info_t *) &wccp2_i_see_you.data[offset];
            break;

        case WCCP2_ROUTER_ID_INFO:

            if (router_identity_info != NULL) {
                debugs(80, DBG_IMPORTANT, "Duplicate router_identity_info definition");
                return;
            }

            router_identity_info = (struct router_identity_info_t *) &wccp2_i_see_you.data[offset];
            break;

        case WCCP2_RTR_VIEW_INFO:

            if (router_view_header != NULL) {
                debugs(80, DBG_IMPORTANT, "Duplicate router_view definition");
                return;
            }

            router_view_header = (struct router_view_t *) &wccp2_i_see_you.data[offset];
            break;

        case WCCP2_CAPABILITY_INFO:

            if (router_capability_header != NULL) {
                debugs(80, DBG_IMPORTANT, "Duplicate router_capability definition");
                return;
            }

            router_capability_header = (struct wccp2_capability_info_header_t *) &wccp2_i_see_you.data[offset];
            break;

            /* Nothing to do for the types below */

        case WCCP2_ASSIGN_MAP:
        case WCCP2_REDIRECT_ASSIGNMENT:
            break;

        default:
            debugs(80, DBG_IMPORTANT, "Unknown record type in WCCPv2 Packet (" << ntohs(header->type) << ").");
        }

        offset += sizeof(struct wccp2_item_header_t);
        offset += ntohs(header->length);

        if (offset > data_length) {
            debugs(80, DBG_IMPORTANT, "Error: WCCPv2 packet tried to tell us there is data beyond the end of the packet");
            return;
        }
    }

    if ((security_info == NULL) || (service_info == NULL) || (router_identity_info == NULL) || (router_view_header == NULL)) {
        debugs(80, DBG_IMPORTANT, "Incomplete WCCPv2 Packet");
        return;
    }

    debugs(80, 5, "Complete packet received");

    /* Check that the service in the packet is configured on this router */
    service_list_ptr = wccp2_service_list_head;

    while (service_list_ptr != NULL) {
        if (service_info->service_id == service_list_ptr->service_info->service_id) {
            break;
        }

        service_list_ptr = service_list_ptr->next;
    }

    if (service_list_ptr == NULL) {
        debugs(80, DBG_IMPORTANT, "WCCPv2 Unknown service received from router (" << service_info->service_id << ")");
        return;
    }

    if (ntohl(security_info->security_option) != ntohl(service_list_ptr->security_info->security_option)) {
        debugs(80, DBG_IMPORTANT, "Invalid security option in WCCPv2 Packet (" << ntohl(security_info->security_option) << " vs " << ntohl(service_list_ptr->security_info->security_option) << ").");
        return;
    }

    if (!wccp2_check_security(service_list_ptr, (char *) security_info, (char *) &wccp2_i_see_you, len)) {
        debugs(80, DBG_IMPORTANT, "Received WCCPv2 Packet failed authentication");
        return;
    }

    /* Check that the router address is configured on this router */
    for (router_list_ptr = &service_list_ptr->router_list_head; router_list_ptr->next != NULL; router_list_ptr = router_list_ptr->next) {
        if (router_list_ptr->router_sendto_address.s_addr == from.sin_addr.s_addr)
            break;
    }

    if (router_list_ptr->next == NULL) {
        debugs(80, DBG_IMPORTANT, "WCCPv2 Packet received from unknown router");
        return;
    }

    /* Set the router id */
    router_list_ptr->info->router_address = router_identity_info->router_id_element.router_address;

    /* Increment the received id in the packet */
    if (ntohl(router_list_ptr->info->received_id) != ntohl(router_identity_info->router_id_element.received_id)) {
        debugs(80, 3, "Incoming WCCP2_I_SEE_YOU Received ID old=" << ntohl(router_list_ptr->info->received_id) << " new=" << ntohl(router_identity_info->router_id_element.received_id) << ".");
        router_list_ptr->info->received_id = router_identity_info->router_id_element.received_id;
    }

    /* TODO: check return/forwarding methods */
    if (router_capability_header == NULL) {
        if ((Config.Wccp2.return_method != WCCP2_PACKET_RETURN_METHOD_GRE) || (Config.Wccp2.forwarding_method != WCCP2_FORWARDING_METHOD_GRE)) {
            debugs(80, DBG_IMPORTANT, "wccp2HandleUdp: fatal error - A WCCP router does not support the forwarding method specified, only GRE supported");
            wccp2ConnectionClose();
            return;
        }
    } else {

        char *end = ((char *) router_capability_header) + sizeof(*router_capability_header) + ntohs(router_capability_header->capability_info_length) - sizeof(struct wccp2_capability_info_header_t);

        router_capability_element = (struct wccp2_capability_element_t *) (((char *) router_capability_header) + sizeof(*router_capability_header));

        while ((char *) router_capability_element <= end) {

            switch (ntohs(router_capability_element->capability_type)) {

            case WCCP2_CAPABILITY_FORWARDING_METHOD:

                if (!(ntohl(router_capability_element->capability_value) & Config.Wccp2.forwarding_method)) {
                    debugs(80, DBG_IMPORTANT, "wccp2HandleUdp: fatal error - A WCCP router has specified a different forwarding method " << ntohl(router_capability_element->capability_value) << ", expected " << Config.Wccp2.forwarding_method);
                    wccp2ConnectionClose();
                    return;
                }

                break;

            case WCCP2_CAPABILITY_ASSIGNMENT_METHOD:

                if (!(ntohl(router_capability_element->capability_value) & Config.Wccp2.assignment_method)) {
                    debugs(80, DBG_IMPORTANT, "wccp2HandleUdp: fatal error - A WCCP router has specified a different assignment method " << ntohl(router_capability_element->capability_value) << ", expected "<< Config.Wccp2.assignment_method);
                    wccp2ConnectionClose();
                    return;
                }

                break;

            case WCCP2_CAPABILITY_RETURN_METHOD:

                if (!(ntohl(router_capability_element->capability_value) & Config.Wccp2.return_method)) {
                    debugs(80, DBG_IMPORTANT, "wccp2HandleUdp: fatal error - A WCCP router has specified a different return method " << ntohl(router_capability_element->capability_value) << ", expected " << Config.Wccp2.return_method);
                    wccp2ConnectionClose();
                    return;
                }

                break;

            case 4:
            case 5:
                break; // ignore silently for now

            default:
                debugs(80, DBG_IMPORTANT, "Unknown capability type in WCCPv2 Packet (" << ntohs(router_capability_element->capability_type) << ").");
            }

            router_capability_element = (struct wccp2_capability_element_t *) (((char *) router_capability_element) + sizeof(struct wccp2_item_header_t) + ntohs(router_capability_element->capability_length));
        }
    }

    debugs(80, 5, "Cleaning out cache list");
    /* clean out the old cache list */

    for (cache_list_ptr = &router_list_ptr->cache_list_head; cache_list_ptr; cache_list_ptr = cache_list_ptr_next) {
        cache_list_ptr_next = cache_list_ptr->next;

        if (cache_list_ptr != &router_list_ptr->cache_list_head) {
            xfree(cache_list_ptr);
        }
    }

    router_list_ptr->num_caches = htonl(0);
    num_caches = 0;

    /* Check to see if we're the master cache and update the cache list */
    found = 0;
    service_list_ptr->lowest_ip = 1;
    cache_list_ptr = &router_list_ptr->cache_list_head;

    /* to find the list of caches, we start at the end of the router view header */

    ptr = (char *) (router_view_header) + sizeof(struct router_view_t);

    /* Then we read the number of routers */
    memcpy(&tmp, ptr, sizeof(tmp));

    /* skip the number plus all the ip's */

    ptr += sizeof(tmp) + (ntohl(tmp) * sizeof(struct in_addr));

    /* Then read the number of caches */
    memcpy(&tmp, ptr, sizeof(tmp));
    ptr += sizeof(tmp);

    if (ntohl(tmp) != 0) {
        /* search through the list of received-from ip addresses */

        for (num_caches = 0; num_caches < (int) ntohl(tmp); ++num_caches) {
            /* Get a copy of the ip */
            memset(&cache_address, 0, sizeof(cache_address)); // Make GCC happy

            switch (Config.Wccp2.assignment_method) {

            case WCCP2_ASSIGNMENT_METHOD_HASH:

                cache_identity = (struct wccp2_cache_identity_info_t *) ptr;

                ptr += sizeof(struct wccp2_cache_identity_info_t);

                memcpy(&cache_address, &cache_identity->addr, sizeof(struct in_addr));

                cache_list_ptr->weight = ntohs(cache_identity->weight);
                break;

            case WCCP2_ASSIGNMENT_METHOD_MASK:

                cache_mask_info = (struct cache_mask_info_t *) ptr;

                /* The mask assignment has an undocumented variable length entry here */

                if (ntohl(cache_mask_info->num1) == 3) {

                    cache_mask_identity = (struct wccp2_cache_mask_identity_info_t *) ptr;

                    ptr += sizeof(struct wccp2_cache_mask_identity_info_t);

                    memcpy(&cache_address, &cache_mask_identity->addr, sizeof(struct in_addr));
                } else {

                    ptr += sizeof(struct cache_mask_info_t);

                    memcpy(&cache_address, &cache_mask_info->addr, sizeof(struct in_addr));
                }

                cache_list_ptr->weight = 0;
                break;

            default:
                fatalf("Unknown Wccp2 assignment method\n");
            }

            /* Update the cache list */
            cache_list_ptr->cache_ip = cache_address;

            cache_list_ptr->next = (wccp2_cache_list_t*) xcalloc(1, sizeof(struct wccp2_cache_list_t));

            cache_list_ptr = cache_list_ptr->next;

            cache_list_ptr->next = NULL;

            debugs (80, 5,  "checking cache list: (" << std::hex << cache_address.s_addr << ":" <<  router_list_ptr->local_ip.s_addr << ")");

            /* Check to see if it's the master, or us */

            if (cache_address.s_addr == router_list_ptr->local_ip.s_addr) {
                found = 1;
            }

            if (cache_address.s_addr < router_list_ptr->local_ip.s_addr) {
                service_list_ptr->lowest_ip = 0;
            }
        }
    } else {
        debugs(80, 5, "Adding ourselves as the only cache");

        /* Update the cache list */
        cache_list_ptr->cache_ip = router_list_ptr->local_ip;

        cache_list_ptr->next = (wccp2_cache_list_t*) xcalloc(1, sizeof(struct wccp2_cache_list_t));
        cache_list_ptr = cache_list_ptr->next;
        cache_list_ptr->next = NULL;

        service_list_ptr->lowest_ip = 1;
        found = 1;
        num_caches = 1;
    }

    wccp2SortCacheList(&router_list_ptr->cache_list_head);

    router_list_ptr->num_caches = htonl(num_caches);

    if ((found == 1) && (service_list_ptr->lowest_ip == 1)) {
        if (ntohl(router_view_header->change_number) != router_list_ptr->member_change) {
            debugs(80, 4, "Change detected - queueing up new assignment");
            router_list_ptr->member_change = ntohl(router_view_header->change_number);
            eventDelete(wccp2AssignBuckets, NULL);
            eventAdd("wccp2AssignBuckets", wccp2AssignBuckets, NULL, 15.0, 1);
        } else {
            debugs(80, 5, "Change not detected (" << ntohl(router_view_header->change_number) << " = " << router_list_ptr->member_change << ")");
        }
    } else {
        eventDelete(wccp2AssignBuckets, NULL);
        debugs(80, 5, "I am not the lowest ip cache - not assigning buckets");
    }
}
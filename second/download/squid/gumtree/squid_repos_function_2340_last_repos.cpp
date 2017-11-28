static void
wccp2AssignBuckets(void *)
{
    struct wccp2_service_list_t *service_list_ptr;

    struct wccp2_router_list_t *router_list_ptr;

    struct wccp2_cache_list_t *cache_list_ptr;
    char wccp_packet[WCCP_RESPONSE_SIZE];
    short int offset, saved_offset, assignment_offset, alt_assignment_offset;

    struct sockaddr_in router;
    int router_len;
    int bucket_counter;
    uint32_t service_flags;
    unsigned short port = WCCP_PORT;

    /* Packet segments */

    struct wccp2_message_header_t *main_header;

    struct wccp2_security_md5_t *security = NULL;
    /* service from service struct */

    struct wccp2_item_header_t *assignment_header;

    struct wccp2_item_header_t *alt_assignment_type_header = NULL;

    struct assignment_key_t *assignment_key;
    /* number of routers */

    struct wccp2_router_assign_element_t *router_assign;
    /* number of caches */

    struct in_addr *cache_address;
    /* Alternative assignement mask/values */
    int num_maskval;

    struct wccp2_mask_element_t *mask_element;

    struct wccp2_value_element_t *value_element;
    int valuecounter, value;
    char *buckets;

    assignment_offset = alt_assignment_offset = 0;

    router_len = sizeof(router);
    memset(&router, '\0', router_len);
    router.sin_family = AF_INET;
    router.sin_port = htons(port);

    /* Start main header - fill in length later */
    offset = 0;

    main_header = (struct wccp2_message_header_t *) &wccp_packet[offset];
    main_header->type = htonl(WCCP2_REDIRECT_ASSIGN);
    main_header->version = htons(WCCP2_VERSION);

    debugs(80, 2, "Running wccp2AssignBuckets");
    service_list_ptr = wccp2_service_list_head;

    while (service_list_ptr != NULL) {
        /* If we're not the lowest, we don't need to worry */

        if (service_list_ptr->lowest_ip == 0) {
            /* XXX eww */
            service_list_ptr = service_list_ptr->next;
            continue;
        }

        /* reset the offset */

        offset = sizeof(struct wccp2_message_header_t);

        /* build packet header from hereIam packet */
        /* Security info */
        /* XXX this should be made more generic! */
        /* XXX and I hate magic numbers! */
        switch (service_list_ptr->wccp2_security_type) {

        case WCCP2_NO_SECURITY:

            security = (struct wccp2_security_md5_t *) &wccp_packet[offset];
            memcpy(security, service_list_ptr->security_info, 8);
            offset += 8;
            break;

        case WCCP2_MD5_SECURITY:

            security = (struct wccp2_security_md5_t *) &wccp_packet[offset];

            memcpy(security, service_list_ptr->security_info, sizeof(struct wccp2_security_md5_t));

            offset += sizeof(struct wccp2_security_md5_t);
            break;

        default:
            fatalf("Unknown Wccp2 security type\n");
        }

        /* Service info */

        memcpy(&wccp_packet[offset], service_list_ptr->service_info, sizeof(struct wccp2_service_info_t));

        offset += sizeof(struct wccp2_service_info_t);

        /* assignment header - fill in length later */

        assignment_header = (struct wccp2_item_header_t *) &wccp_packet[offset];

        switch (Config.Wccp2.assignment_method) {

        case WCCP2_ASSIGNMENT_METHOD_HASH:
            assignment_header->type = htons(WCCP2_REDIRECT_ASSIGNMENT);

            offset += sizeof(struct wccp2_item_header_t);
            assignment_offset = offset;
            break;

        case WCCP2_ASSIGNMENT_METHOD_MASK:
            assignment_header->type = htons(WCCP2_ALT_ASSIGNMENT);

            offset += sizeof(struct wccp2_item_header_t);
            assignment_offset = offset;

            /* The alternative assignment has an extra header, fill in length later */

            alt_assignment_type_header = (struct wccp2_item_header_t *) &wccp_packet[offset];
            alt_assignment_type_header->type = htons(WCCP2_MASK_ASSIGNMENT);

            offset += sizeof(struct wccp2_item_header_t);
            alt_assignment_offset = offset;

            break;

        default:
            fatalf("Unknown Wccp2 assignment method\n");
        }

        /* Assignment key - fill in master ip later */

        assignment_key = (struct assignment_key_t *) &wccp_packet[offset];

        assignment_key->master_number = htonl(++service_list_ptr->change_num);

        offset += sizeof(struct assignment_key_t);

        /* Number of routers */
        memcpy(&wccp_packet[offset], &service_list_ptr->num_routers, sizeof(service_list_ptr->num_routers));

        offset += sizeof(service_list_ptr->num_routers);

        for (router_list_ptr = &service_list_ptr->router_list_head; router_list_ptr->next != NULL; router_list_ptr = router_list_ptr->next) {

            /* Add routers */

            router_assign = (struct wccp2_router_assign_element_t *) &wccp_packet[offset];
            router_assign->router_address = router_list_ptr->info->router_address;
            router_assign->received_id = router_list_ptr->info->received_id;
            router_assign->change_number = htonl(router_list_ptr->member_change);

            offset += sizeof(struct wccp2_router_assign_element_t);
        }

        saved_offset = offset;

        for (router_list_ptr = &service_list_ptr->router_list_head; router_list_ptr->next != NULL; router_list_ptr = router_list_ptr->next) {
            unsigned long *weight = (unsigned long *)xcalloc(sizeof(*weight), ntohl(router_list_ptr->num_caches));
            unsigned long total_weight = 0;
            int num_caches = ntohl(router_list_ptr->num_caches);

            offset = saved_offset;

            switch (Config.Wccp2.assignment_method) {

            case WCCP2_ASSIGNMENT_METHOD_HASH:
                /* Number of caches */
                memcpy(&wccp_packet[offset], &router_list_ptr->num_caches, sizeof(router_list_ptr->num_caches));
                offset += sizeof(router_list_ptr->num_caches);

                if (num_caches) {
                    int cache;

                    for (cache = 0, cache_list_ptr = &router_list_ptr->cache_list_head; cache_list_ptr->next; cache_list_ptr = cache_list_ptr->next, ++cache) {
                        /* add caches */

                        cache_address = (struct in_addr *) &wccp_packet[offset];

                        memcpy(cache_address, &cache_list_ptr->cache_ip, sizeof(struct in_addr));
                        total_weight += cache_list_ptr->weight << 12;
                        weight[cache] = cache_list_ptr->weight << 12;

                        offset += sizeof(struct in_addr);
                    }
                }

                /* Add buckets */
                buckets = (char *) &wccp_packet[offset];

                memset(buckets, '\0', WCCP_BUCKETS);

                if (num_caches != 0) {
                    if (total_weight == 0) {
                        for (bucket_counter = 0; bucket_counter < WCCP_BUCKETS; ++bucket_counter) {
                            buckets[bucket_counter] = (char) (bucket_counter % num_caches);
                        }
                    } else {
                        unsigned long *assigned = (unsigned long *)xcalloc(sizeof(*assigned), num_caches);
                        unsigned long done = 0;
                        int cache = -1;
                        unsigned long per_bucket = total_weight / WCCP_BUCKETS;

                        for (bucket_counter = 0; bucket_counter < WCCP_BUCKETS; ++bucket_counter) {
                            int n;
                            unsigned long step;

                            for (n = num_caches; n; --n) {
                                ++cache;

                                if (cache >= num_caches)
                                    cache = 0;

                                if (!weight[cache]) {
                                    ++n;
                                    continue;
                                }

                                if (assigned[cache] <= done)
                                    break;
                            }

                            buckets[bucket_counter] = (char) cache;
                            step = per_bucket * total_weight / weight[cache];
                            assigned[cache] += step;
                            done += per_bucket;
                        }

                        safe_free(assigned);
                    }
                }

                offset += (WCCP_BUCKETS * sizeof(char));
                safe_free(weight);
                break;

            case WCCP2_ASSIGNMENT_METHOD_MASK:
                num_maskval = htonl(1);
                memcpy(&wccp_packet[offset], &num_maskval, sizeof(int));
                offset += sizeof(int);

                mask_element = (struct wccp2_mask_element_t *) &wccp_packet[offset];
                service_flags = ntohl(service_list_ptr->service_info->service_flags);

                if ((service_flags & WCCP2_SERVICE_SRC_IP_HASH) || (service_flags & WCCP2_SERVICE_SRC_IP_ALT_HASH)) {
                    mask_element->source_ip_mask = htonl(0x00001741);
                    mask_element->dest_ip_mask = 0;
                    mask_element->source_port_mask = 0;
                    mask_element->dest_port_mask = 0;
                } else if ((service_list_ptr->info.service == WCCP2_SERVICE_STANDARD) || (service_flags & WCCP2_SERVICE_DST_IP_HASH) || (service_flags & WCCP2_SERVICE_DST_IP_ALT_HASH)) {
                    mask_element->source_ip_mask = 0;
                    mask_element->dest_ip_mask = htonl(0x00001741);
                    mask_element->source_port_mask = 0;
                    mask_element->dest_port_mask = 0;
                } else if ((service_flags & WCCP2_SERVICE_SRC_PORT_HASH) || (service_flags & WCCP2_SERVICE_SRC_PORT_ALT_HASH)) {
                    mask_element->source_ip_mask = 0;
                    mask_element->dest_ip_mask = 0;
                    mask_element->source_port_mask = htons(0x1741);
                    mask_element->dest_port_mask = 0;
                } else if ((service_flags & WCCP2_SERVICE_DST_PORT_HASH) || (service_flags & WCCP2_SERVICE_DST_PORT_ALT_HASH)) {
                    mask_element->source_ip_mask = 0;
                    mask_element->dest_ip_mask = 0;
                    mask_element->source_port_mask = 0;
                    mask_element->dest_port_mask = htons(0x1741);
                } else {
                    fatalf("Unknown service hash method\n");
                }

                mask_element->number_values = htonl(64);

                offset += sizeof(struct wccp2_mask_element_t);

                cache_list_ptr = &router_list_ptr->cache_list_head;
                value = 0;

                for (valuecounter = 0; valuecounter < 64; ++valuecounter) {

                    value_element = (struct wccp2_value_element_t *) &wccp_packet[offset];

                    /* Update the value according the the "correct" formula */

                    for (; (value & 0x1741) != value; ++value) {
                        assert(value <= 0x1741);
                    }

                    if ((service_flags & WCCP2_SERVICE_SRC_IP_HASH) || (service_flags & WCCP2_SERVICE_SRC_IP_ALT_HASH)) {
                        value_element->source_ip_value = htonl(value);
                        value_element->dest_ip_value = 0;
                        value_element->source_port_value = 0;
                        value_element->dest_port_value = 0;
                    } else if ((service_list_ptr->info.service == WCCP2_SERVICE_STANDARD) || (service_flags & WCCP2_SERVICE_DST_IP_HASH) || (service_flags & WCCP2_SERVICE_DST_IP_ALT_HASH)) {
                        value_element->source_ip_value = 0;
                        value_element->dest_ip_value = htonl(value);
                        value_element->source_port_value = 0;
                        value_element->dest_port_value = 0;
                    } else if ((service_flags & WCCP2_SERVICE_SRC_PORT_HASH) || (service_flags & WCCP2_SERVICE_SRC_PORT_ALT_HASH)) {
                        value_element->source_ip_value = 0;
                        value_element->dest_ip_value = 0;
                        value_element->source_port_value = htons(value);
                        value_element->dest_port_value = 0;
                    } else if ((service_flags & WCCP2_SERVICE_DST_PORT_HASH) || (service_flags & WCCP2_SERVICE_DST_PORT_ALT_HASH)) {
                        value_element->source_ip_value = 0;
                        value_element->dest_ip_value = 0;
                        value_element->source_port_value = 0;
                        value_element->dest_port_value = htons(value);
                    } else {
                        fatalf("Unknown service hash method\n");
                    }

                    value_element->cache_ip = cache_list_ptr->cache_ip;

                    offset += sizeof(struct wccp2_value_element_t);
                    ++value;

                    /* Assign the next value to the next cache */

                    if ((cache_list_ptr->next) && (cache_list_ptr->next->next))
                        cache_list_ptr = cache_list_ptr->next;
                    else
                        cache_list_ptr = &router_list_ptr->cache_list_head;
                }

                /* Fill in length */
                alt_assignment_type_header->length = htons(offset - alt_assignment_offset);

                break;

            default:
                fatalf("Unknown Wccp2 assignment method\n");
            }

            /* Fill in length */

            assignment_header->length = htons(offset - assignment_offset);

            /* Fill in assignment key */
            assignment_key->master_ip = router_list_ptr->local_ip;

            /* finish length */

            main_header->length = htons(offset - sizeof(struct wccp2_message_header_t));

            /* set the destination address */
            router.sin_addr = router_list_ptr->router_sendto_address;

            /* Security update, if needed */

            if (service_list_ptr->wccp2_security_type == WCCP2_MD5_SECURITY) {
                wccp2_update_md5_security(service_list_ptr->wccp_password, (char *) security, wccp_packet, offset);
            }

            if (ntohl(router_list_ptr->num_caches)) {
                /* send packet */

                /* FIXME INET6 : drop temp conversion */
                Ip::Address tmp_rtr(router);

                if (wccp2_numrouters > 1) {
                    comm_udp_sendto(theWccp2Connection,
                                    tmp_rtr,
                                    &wccp_packet,
                                    offset);
                } else {
                    if (send(theWccp2Connection, &wccp_packet, offset, 0) < static_cast<int>(offset)) {
                        int xerrno = errno;
                        debugs(80, 2, "ERROR: failed to send WCCPv2 HERE_I_AM packet to " << tmp_rtr << " : " << xstrerr(xerrno));
                    }
                }
            }
            safe_free(weight);
        }

        service_list_ptr = service_list_ptr->next;
    }
}
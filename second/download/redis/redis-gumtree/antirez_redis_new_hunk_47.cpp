    uint32_t totlen = ntohl(hdr->totlen);
    uint16_t type = ntohs(hdr->type);

    if (type < CLUSTERMSG_TYPE_COUNT)
        server.cluster->stats_bus_messages_received[type]++;
    serverLog(LL_DEBUG,"--- Processing packet of type %d, %lu bytes",
        type, (unsigned long) totlen);


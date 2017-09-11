        clusterUpdateSlotsConfigWith(n,reportedConfigEpoch,
            hdr->data.update.nodecfg.slots);
    } else {
        serverLog(REDIS_WARNING,"Received unknown packet type: %d", type);
    }
    return 1;
}

    if (strstr(r->element[2]->str,server.runid) != NULL) return;

    {
        /* Format is composed of 8 tokens:
         * 0=ip,1=port,2=runid,3=current_epoch,4=master_name,
         * 5=master_ip,6=master_port,7=master_config_epoch. */
        int numtokens, port, removed, master_port;
        uint64_t current_epoch, master_config_epoch;
        char **token = sdssplitlen(r->element[2]->str,
                                   r->element[2]->len,
                                   ",",1,&numtokens);
        sentinelRedisInstance *si;

        if (numtokens == 8) {
            /* First, try to see if we already have this sentinel. */
            port = atoi(token[1]);
            master_port = atoi(token[6]);
            si = getSentinelRedisInstanceByAddrAndRunID(
                            master->sentinels,token[0],port,token[2]);
            current_epoch = strtoull(token[3],NULL,10);
            master_config_epoch = strtoull(token[7],NULL,10);
            sentinelRedisInstance *msgmaster;

            if (!si) {
                /* If not, remove all the sentinels that have the same runid
                 * OR the same ip/port, because it's either a restart or a
                 * network topology change. */
                removed = removeMatchingSentinelsFromMaster(master,token[0],port,
                                token[2]);
                if (removed) {
                    sentinelEvent(REDIS_NOTICE,"-dup-sentinel",master,
                        "%@ #duplicate of %s:%d or %s",
                        token[0],port,token[2]);
                }

                /* Add the new sentinel. */
                si = createSentinelRedisInstance(NULL,SRI_SENTINEL,
                                token[0],port,master->quorum,master);
                if (si) {
                    sentinelEvent(REDIS_NOTICE,"+sentinel",si,"%@");
                    /* The runid is NULL after a new instance creation and
                     * for Sentinels we don't have a later chance to fill it,
                     * so do it now. */
                    si->runid = sdsnew(token[2]);
                    sentinelFlushConfig();
                }
            }

            /* Update local current_epoch if received current_epoch is greater.*/
            if (current_epoch > sentinel.current_epoch) {
                sentinel.current_epoch = current_epoch;
                sentinelEvent(REDIS_WARNING,"+new-epoch",ri,"%llu",
                    (unsigned long long) sentinel.current_epoch);
            }

            /* Update master info if received configuration is newer. */
            if ((msgmaster = sentinelGetMasterByName(token[4])) != NULL) {
                if (msgmaster->config_epoch < master_config_epoch) {
                    msgmaster->config_epoch = master_config_epoch;
                    if (master_port != msgmaster->addr->port ||
                        !strcmp(msgmaster->addr->ip, token[5]))
                    {
                        sentinelAddr *old_addr;

                        sentinelEvent(REDIS_WARNING,"+switch-master",
                            msgmaster,"%s %s %d %s %d",
                            msgmaster->name,
                            msgmaster->addr->ip, msgmaster->addr->port,
                            token[5], master_port);

                        old_addr = dupSentinelAddr(msgmaster->addr);
                        sentinelResetMasterAndChangeAddress(msgmaster,
                                                    token[5], master_port);
                        sentinelCallClientReconfScript(msgmaster,
                            SENTINEL_OBSERVER,"start",
                            old_addr,msgmaster->addr);
                        releaseSentinelAddr(old_addr);
                    }
                }
            }

            /* Update the state of the Sentinel. */
            if (si) si->last_hello_time = mstime();
        }
        sdsfreesplitres(token,numtokens);
    }
}

/* Send an "Hello" message via Pub/Sub to the specified 'ri' Redis
 * instance in order to broadcast the current configuraiton for this
 * master, and to advertise the existence of this Sentinel at the same time.
 *
 * The message has the following format:
 *
 * sentinel_ip,sentinel_port,sentinel_runid,current_epoch,
 * master_name,master_ip,master_port,master_config_epoch.
 *
 * Returns REDIS_OK if the PUBLISH was queued correctly, otherwise
 * REDIS_ERR is returned. */
int sentinelSendHello(sentinelRedisInstance *ri) {
    char ip[REDIS_IP_STR_LEN];
    char payload[REDIS_IP_STR_LEN+1024];
    int retval;
    sentinelRedisInstance *master = (ri->flags & SRI_MASTER) ? ri : ri->master;
    sentinelAddr *master_addr = sentinelGetCurrentMasterAddress(master);

    /* Try to obtain our own IP address. */
    if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) == -1) return REDIS_ERR;
    if (ri->flags & SRI_DISCONNECTED) return REDIS_ERR;

    /* Format and send the Hello message. */
    snprintf(payload,sizeof(payload),
        "%s,%d,%s,%llu," /* Info about this sentinel. */
        "%s,%s,%d,%lld", /* Info about current master. */
        ip, server.port, server.runid,
        (unsigned long long) sentinel.current_epoch,
        /* --- */
        master->name,master_addr->ip,master_addr->port,
        master->config_epoch);
    retval = redisAsyncCommand(ri->cc,
        sentinelPublishReplyCallback, NULL, "PUBLISH %s %s",
            SENTINEL_HELLO_CHANNEL,payload);
    if (retval != REDIS_OK) return REDIS_ERR;
    ri->pending_commands++;
    return REDIS_OK;
}

/* Send periodic PING, INFO, and PUBLISH to the Hello channel to
 * the specified master or slave instance. */
void sentinelPingInstance(sentinelRedisInstance *ri) {
    mstime_t now = mstime();
    mstime_t info_period;

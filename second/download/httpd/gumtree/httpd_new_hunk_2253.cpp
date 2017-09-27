
BOOL ssl_scache_shmcb_store(server_rec *s, UCHAR *id, int idlen,
                           time_t timeout, SSL_SESSION * pSession)
{
    SSLModConfigRec *mc = myModConfig(s);
    BOOL to_return = FALSE;
    unsigned char encoded[SSL_SESSION_MAX_DER];
    unsigned char *ptr_encoded;
    unsigned int len_encoded;
    SHMCBHeader *header = mc->tSessionCacheDataTable;
    SHMCBSubcache *subcache = SHMCB_MASK(header, id);

    ssl_mutex_on(s);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "ssl_scache_shmcb_store (0x%02x -> subcache %d)",
                 SHMCB_MASK_DBG(header, id));
    if (idlen < 4) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "unusably short session_id provided "
                "(%u bytes)", idlen);
        goto done;
    }
    /* Serialise the session. */
    len_encoded = i2d_SSL_SESSION(pSession, NULL);
    if (len_encoded > SSL_SESSION_MAX_DER) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "session is too big (%u bytes)", len_encoded);
        goto done;
    }
    ptr_encoded = encoded;
    len_encoded = i2d_SSL_SESSION(pSession, &ptr_encoded);
    if (!shmcb_subcache_store(s, header, subcache, encoded,
                              len_encoded, id, timeout)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "can't store a session!");
        goto done;
    }
    header->stat_stores++;
    to_return = TRUE;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving ssl_scache_shmcb_store successfully");
done:
    ssl_mutex_off(s);
    return to_return;
}

SSL_SESSION *ssl_scache_shmcb_retrieve(server_rec *s, UCHAR *id, int idlen)
{
    SSLModConfigRec *mc = myModConfig(s);
    SSL_SESSION *pSession = NULL;
    SHMCBHeader *header = mc->tSessionCacheDataTable;
    SHMCBSubcache *subcache = SHMCB_MASK(header, id);

    ssl_mutex_on(s);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "ssl_scache_shmcb_retrieve (0x%02x -> subcache %d)",
                 SHMCB_MASK_DBG(header, id));
    if (idlen < 4) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "unusably short session_id provided "
                "(%u bytes)", idlen);
        goto done;
    }
    /* Get the session corresponding to the session_id or NULL if it doesn't
     * exist (or is flagged as "removed"). */
    pSession = shmcb_subcache_retrieve(s, header, subcache, id, idlen);
    if (pSession)
        header->stat_retrieves_hit++;
    else
        header->stat_retrieves_miss++;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving ssl_scache_shmcb_retrieve successfully");
done:
    ssl_mutex_off(s);
    return pSession;
}

void ssl_scache_shmcb_remove(server_rec *s, UCHAR *id, int idlen)
{
    SSLModConfigRec *mc = myModConfig(s);
    SHMCBHeader *header = mc->tSessionCacheDataTable;
    SHMCBSubcache *subcache = SHMCB_MASK(header, id);

    ssl_mutex_on(s);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "ssl_scache_shmcb_remove (0x%02x -> subcache %d)",
                 SHMCB_MASK_DBG(header, id));
    if (idlen < 4) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "unusably short session_id provided "
                "(%u bytes)", idlen);
        goto done;
    }
    if (shmcb_subcache_remove(s, header, subcache, id, idlen))
        header->stat_removes_hit++;
    else
        header->stat_removes_miss++;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving ssl_scache_shmcb_remove successfully");
done:
    ssl_mutex_off(s);
}

void ssl_scache_shmcb_status(request_rec *r, int flags, apr_pool_t *p)
{
    server_rec *s = r->server;
    SSLModConfigRec *mc = myModConfig(s);
    void *shm_segment = apr_shm_baseaddr_get(mc->pSessionCacheDataMM);
    SHMCBHeader *header = shm_segment;
    unsigned int loop, total = 0, cache_total = 0, non_empty_subcaches = 0;
    time_t idx_expiry, min_expiry = 0, max_expiry = 0, average_expiry = 0;
    time_t now = time(NULL);
    double expiry_total = 0;
    int index_pct, cache_pct;

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "inside shmcb_status");
    /* Perform the iteration inside the mutex to avoid corruption or invalid
     * pointer arithmetic. The rest of our logic uses read-only header data so
     * doesn't need the lock. */
    ssl_mutex_on(s);
    /* Iterate over the subcaches */
    for (loop = 0; loop < header->subcache_num; loop++) {
        SHMCBSubcache *subcache = SHMCB_SUBCACHE(header, loop);
        shmcb_subcache_expire(s, header, subcache);
        total += subcache->idx_used;
        cache_total += subcache->data_used;
        if (subcache->idx_used) {
            SHMCBIndex *idx = SHMCB_INDEX(subcache, subcache->idx_pos);
            non_empty_subcaches++;
            idx_expiry = idx->expires;
            expiry_total += (double)idx_expiry;
            max_expiry = ((idx_expiry > max_expiry) ? idx_expiry : max_expiry);
            if (!min_expiry)
                min_expiry = idx_expiry;
            else
                min_expiry = ((idx_expiry < min_expiry) ? idx_expiry : min_expiry);
        }
    }
    ssl_mutex_off(s);
    index_pct = (100 * total) / (header->index_num *
                                 header->subcache_num);
    cache_pct = (100 * cache_total) / (header->subcache_data_size *
                                       header->subcache_num);
    /* Generate HTML */
    ap_rprintf(r, "cache type: <b>SHMCB</b>, shared memory: <b>%d</b> "
               "bytes, current sessions: <b>%d</b><br>",
               mc->nSessionCacheDataSize, total);
    ap_rprintf(r, "subcaches: <b>%d</b>, indexes per subcache: <b>%d</b><br>",
               header->subcache_num, header->index_num);
    if (non_empty_subcaches) {
        average_expiry = (time_t)(expiry_total / (double)non_empty_subcaches);
        ap_rprintf(r, "time left on oldest entries' SSL sessions: ");
        if (now < average_expiry)
            ap_rprintf(r, "avg: <b>%d</b> seconds, (range: %d...%d)<br>",
                       (int)(average_expiry - now),
                       (int)(min_expiry - now),
                       (int)(max_expiry - now));
        else
            ap_rprintf(r, "expiry_threshold: <b>Calculation error!</b><br>");
    }

    ap_rprintf(r, "index usage: <b>%d%%</b>, cache usage: <b>%d%%</b><br>",
               index_pct, cache_pct);
    ap_rprintf(r, "total sessions stored since starting: <b>%lu</b><br>",
               header->stat_stores);
    ap_rprintf(r, "total sessions expired since starting: <b>%lu</b><br>",
               header->stat_expiries);
    ap_rprintf(r, "total (pre-expiry) sessions scrolled out of the cache: "
               "<b>%lu</b><br>", header->stat_scrolled);
    ap_rprintf(r, "total retrieves since starting: <b>%lu</b> hit, "
               "<b>%lu</b> miss<br>", header->stat_retrieves_hit,
               header->stat_retrieves_miss);
    ap_rprintf(r, "total removes since starting: <b>%lu</b> hit, "
               "<b>%lu</b> miss<br>", header->stat_removes_hit,
               header->stat_removes_miss);
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "leaving shmcb_status");
}

/*
 * Subcache-level cache operations 
 */

static void shmcb_subcache_expire(server_rec *s, SHMCBHeader *header,
                                  SHMCBSubcache *subcache)
{
    time_t now = time(NULL);
    unsigned int loop = 0;
    unsigned int new_idx_pos = subcache->idx_pos;
    SHMCBIndex *idx = NULL;

    while (loop < subcache->idx_used) {
        idx = SHMCB_INDEX(subcache, new_idx_pos);
        if (idx->expires > now)
            /* it hasn't expired yet, we're done iterating */
            break;
        loop++;
        new_idx_pos = SHMCB_CYCLIC_INCREMENT(new_idx_pos, 1, header->index_num);
    }
    if (!loop)
        /* Nothing to do */
        return;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "will be expiring %u sessions", loop);
    if (loop == subcache->idx_used) {
        /* We're expiring everything, piece of cake */
        subcache->idx_used = 0;
        subcache->data_used = 0;
    } else {
        /* There remain other indexes, so we can use idx to adjust 'data' */
        unsigned int diff = SHMCB_CYCLIC_SPACE(subcache->data_pos,
                                               idx->data_pos,
                                               header->subcache_data_size);
        /* Adjust the indexes */
        subcache->idx_used -= loop;
        subcache->idx_pos = new_idx_pos;
        /* Adjust the data area */
        subcache->data_used -= diff;
        subcache->data_pos = idx->data_pos;
    }
    header->stat_expiries += loop;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "we now have %u sessions", subcache->idx_used);
}

static BOOL shmcb_subcache_store(server_rec *s, SHMCBHeader *header,
                                 SHMCBSubcache *subcache, 
                                 UCHAR *data, unsigned int data_len,
                                 UCHAR *id, time_t expiry)
{
    unsigned int new_offset, new_idx;
    SHMCBIndex *idx;

    /* Sanity check the input */
    if ((data_len > header->subcache_data_size) || (data_len > SSL_SESSION_MAX_DER)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "inserting session larger (%d) than subcache data area (%d)",
                     data_len, header->subcache_data_size);
        return FALSE;
    }

    /* If there are entries to expire, ditch them first. */
    shmcb_subcache_expire(s, header, subcache);

    /* Loop until there is enough space to insert */
    if (header->subcache_data_size - subcache->data_used < data_len
        || subcache->idx_used == header->index_num) {
        unsigned int loop = 0;

        idx = SHMCB_INDEX(subcache, subcache->idx_pos);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "about to force-expire, subcache: idx_used=%d, "
                     "data_used=%d", subcache->idx_used, subcache->data_used);
        do {
            SHMCBIndex *idx2;

            /* Adjust the indexes by one */
            subcache->idx_pos = SHMCB_CYCLIC_INCREMENT(subcache->idx_pos, 1,
                                                       header->index_num);
            subcache->idx_used--;
            if (!subcache->idx_used) {
                /* There's nothing left */
                subcache->data_used = 0;
                break;
            }
            /* Adjust the data */
            idx2 = SHMCB_INDEX(subcache, subcache->idx_pos);
            subcache->data_used -= SHMCB_CYCLIC_SPACE(idx->data_pos, idx2->data_pos,
                                                      header->subcache_data_size);
            subcache->data_pos = idx2->data_pos;
            /* Stats */
            header->stat_scrolled++;
            /* Loop admin */
            idx = idx2;
            loop++;
        } while (header->subcache_data_size - subcache->data_used < data_len);

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "finished force-expire, subcache: idx_used=%d, "
                     "data_used=%d", subcache->idx_used, subcache->data_used);
    }

    /* HERE WE ASSUME THAT THE NEW SESSION SHOULD GO ON THE END! I'M NOT
     * CHECKING WHETHER IT SHOULD BE GENUINELY "INSERTED" SOMEWHERE.
     *
     * We either fix that, or find out at a "higher" (read "mod_ssl")
     * level whether it is possible to have distinct session caches for
     * any attempted tomfoolery to do with different session timeouts.
     * Knowing in advance that we can have a cache-wide constant timeout
     * would make this stuff *MUCH* more efficient. Mind you, it's very
     * efficient right now because I'm ignoring this problem!!!
     */
    /* Insert the data */
    new_offset = SHMCB_CYCLIC_INCREMENT(subcache->data_pos, subcache->data_used,
                                        header->subcache_data_size);
    shmcb_cyclic_ntoc_memcpy(header->subcache_data_size,
                             SHMCB_DATA(header, subcache), new_offset,
                             data, data_len);
    subcache->data_used += data_len;
    /* Insert the index */
    new_idx = SHMCB_CYCLIC_INCREMENT(subcache->idx_pos, subcache->idx_used,
                                     header->index_num);
    idx = SHMCB_INDEX(subcache, new_idx);
    idx->expires = expiry;
    idx->data_pos = new_offset;
    idx->data_used = data_len;
    idx->s_id2 = id[1];
    idx->removed = 0;
    subcache->idx_used++;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "insert happened at idx=%d, data=%d", new_idx, new_offset);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "finished insert, subcache: idx_pos/idx_used=%d/%d, "
                 "data_pos/data_used=%d/%d",
                 subcache->idx_pos, subcache->idx_used,
                 subcache->data_pos, subcache->data_used);
    return TRUE;
}

static SSL_SESSION *shmcb_subcache_retrieve(server_rec *s, SHMCBHeader *header,
                                            SHMCBSubcache *subcache, UCHAR *id,
                                            unsigned int idlen)
{
    unsigned int pos;
    unsigned int loop = 0;

    /* If there are entries to expire, ditch them first. */
    shmcb_subcache_expire(s, header, subcache);
    pos = subcache->idx_pos;

    while (loop < subcache->idx_used) {
        SHMCBIndex *idx = SHMCB_INDEX(subcache, pos);

        /* Only consider 'idx' if;
         * (a) the s_id2 byte matches
         * (b) the "removed" flag isn't set.
         */
        if ((idx->s_id2 == id[1]) && !idx->removed) {
            SSL_SESSION *pSession;
            unsigned char *s_id;
            unsigned int s_idlen;
            unsigned char tempasn[SSL_SESSION_MAX_DER];
            MODSSL_D2I_SSL_SESSION_CONST unsigned char *ptr = tempasn;

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "possible match at idx=%d, data=%d", pos, idx->data_pos);
            /* Copy the data */
            shmcb_cyclic_cton_memcpy(header->subcache_data_size,
                                     tempasn, SHMCB_DATA(header, subcache),
                                     idx->data_pos, idx->data_used);
            /* Decode the session */
            pSession = d2i_SSL_SESSION(NULL, &ptr, idx->data_used);
            if (!pSession) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                             "shmcb_subcache_retrieve internal error");
                return NULL;
            }
            s_id = SSL_SESSION_get_session_id(pSession);
            s_idlen = SSL_SESSION_get_session_id_length(pSession);
            if (s_idlen == idlen && memcmp(s_id, id, idlen) == 0) {
                /* Found the matching session */
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                             "shmcb_subcache_retrieve returning matching session");
                return pSession;
            }
            SSL_SESSION_free(pSession);
        }
        /* Increment */
        loop++;
        pos = SHMCB_CYCLIC_INCREMENT(pos, 1, header->index_num);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "shmcb_subcache_retrieve found no match");
    return NULL;
}

static BOOL shmcb_subcache_remove(server_rec *s, SHMCBHeader *header,
                                  SHMCBSubcache *subcache,
                                  UCHAR *id, unsigned int idlen)
{
    unsigned int pos;
    unsigned int loop = 0;
    BOOL to_return = FALSE;

    /* Unlike the others, we don't do an expire-run first. This is to keep
     * consistent statistics where a "remove" operation may actually be the
     * higher layer spotting an expiry issue prior to us. Our caller is
     * handling stats, so a failure return would be inconsistent if the
     * intended session was in fact removed by an expiry run. */

    pos = subcache->idx_pos;
    while (!to_return && (loop < subcache->idx_used)) {
        SHMCBIndex *idx = SHMCB_INDEX(subcache, pos);
        /* Only consider 'idx' if the s_id2 byte matches and it's not already
         * removed - easiest way to avoid costly ASN decodings. */
        if ((idx->s_id2 == id[1]) && !idx->removed) {
            SSL_SESSION *pSession;
            unsigned char *s_id;
            unsigned int s_idlen;
            unsigned char tempasn[SSL_SESSION_MAX_DER];
            MODSSL_D2I_SSL_SESSION_CONST unsigned char *ptr = tempasn;

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "possible match at idx=%d, data=%d", pos, idx->data_pos);
            /* Copy the data */
            shmcb_cyclic_cton_memcpy(header->subcache_data_size,
                                     tempasn, SHMCB_DATA(header, subcache),
                                     idx->data_pos, idx->data_used);
            /* Decode the session */
            pSession = d2i_SSL_SESSION(NULL, &ptr, idx->data_used);
            if (!pSession) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                             "shmcb_subcache_remove internal error");
                return FALSE;
            }
            s_id = SSL_SESSION_get_session_id(pSession);
            s_idlen = SSL_SESSION_get_session_id_length(pSession);
            if (s_idlen == idlen && memcmp(s_id, id, idlen) == 0) {
                /* Found the matching session, remove it quietly. */
                idx->removed = 1;
                to_return = TRUE;
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                             "shmcb_subcache_remove removing matching session");
            }
            SSL_SESSION_free(pSession);
        }
        /* Increment */
        loop++;
        pos = SHMCB_CYCLIC_INCREMENT(pos, 1, header->index_num);
    }

    return to_return;
}

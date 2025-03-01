
BOOL ssl_scache_shmcb_store(server_rec *s, UCHAR *id, int idlen,
                           time_t timeout, SSL_SESSION * pSession)
{
    SSLModConfigRec *mc = myModConfig(s);
    BOOL to_return = FALSE;

    ssl_mutex_on(s);
    if (!shmcb_store_session(s, mc->tSessionCacheDataTable, id, idlen,
                             pSession, timeout))
        /* in this cache engine, "stores" should never fail. */
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "'shmcb' code was unable to store a "
                     "session in the cache.");
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "shmcb_store successful");
        to_return = TRUE;
    }
    ssl_mutex_off(s);
    return to_return;
}

SSL_SESSION *ssl_scache_shmcb_retrieve(server_rec *s, UCHAR *id, int idlen)
{
    SSLModConfigRec *mc = myModConfig(s);
    SSL_SESSION *pSession;

    ssl_mutex_on(s);
    pSession = shmcb_retrieve_session(s, mc->tSessionCacheDataTable, id, idlen);
    ssl_mutex_off(s);
    if (pSession)
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "shmcb_retrieve had a hit");
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "shmcb_retrieve had a miss");
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                     "Client requested a 'session-resume' but "
                     "we have no such session.");
    }
    return pSession;
}

void ssl_scache_shmcb_remove(server_rec *s, UCHAR *id, int idlen)
{
    SSLModConfigRec *mc = myModConfig(s);

    ssl_mutex_on(s);
    shmcb_remove_session(s, mc->tSessionCacheDataTable, id, idlen);
    ssl_mutex_off(s);
}

void ssl_scache_shmcb_status(request_rec *r, int flags, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(r->server);
    SHMCBHeader *header;
    SHMCBQueue queue;
    SHMCBCache cache;
    SHMCBIndex *idx;
    unsigned int loop, total, cache_total, non_empty_divisions;
    int index_pct, cache_pct;
    double expiry_total;
    time_t average_expiry, now, max_expiry, min_expiry, idxexpiry;

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "inside shmcb_status");

    /* Get the header structure. */
    shmcb_get_header(mc->tSessionCacheDataTable, &header);
    total = cache_total = non_empty_divisions = 0;
    average_expiry = max_expiry = min_expiry = 0;
    expiry_total = 0;

    /* It may seem strange to grab "now" at this point, but in theory
     * we should never have a negative threshold but grabbing "now" after
     * the loop (which performs expiries) could allow that chance. */
    now = time(NULL);
    for (loop = 0; loop <= header->division_mask; loop++) {
        if (shmcb_get_division(header, &queue, &cache, loop)) {
            shmcb_expire_division(r->server, &queue, &cache);
            total += shmcb_get_safe_uint(queue.pos_count);
            cache_total += shmcb_get_safe_uint(cache.pos_count);
            if (shmcb_get_safe_uint(queue.pos_count) > 0) {
                idx = shmcb_get_index(&queue,
                                     shmcb_get_safe_uint(queue.first_pos));
                non_empty_divisions++;
                idxexpiry = shmcb_get_safe_time(&(idx->expires));
                expiry_total += (double) idxexpiry;
                max_expiry = (idxexpiry > max_expiry ? idxexpiry :
                              max_expiry);
                if (min_expiry == 0)
                    min_expiry = idxexpiry;
                else
                    min_expiry = (idxexpiry < min_expiry ? idxexpiry :
                                  min_expiry);
            }
        }
    }
    index_pct = (100 * total) / (header->index_num * (header->division_mask + 1));
    cache_pct = (100 * cache_total) / (header->cache_data_size * (header->division_mask + 1));
    ap_rprintf(r, "cache type: <b>SHMCB</b>, shared memory: <b>%d</b> "
               "bytes, current sessions: <b>%d</b><br>",
               mc->nSessionCacheDataSize, total);
    ap_rprintf(r, "sub-caches: <b>%d</b>, indexes per sub-cache: "
               "<b>%d</b><br>", (int) header->division_mask + 1,
               (int) header->index_num);
    if (non_empty_divisions != 0) {
        average_expiry = (time_t)(expiry_total / (double)non_empty_divisions);
        ap_rprintf(r, "time left on oldest entries' SSL sessions: ");
        if (now < average_expiry)
            ap_rprintf(r, "avg: <b>%d</b> seconds, (range: %d...%d)<br>",
                       (int)(average_expiry - now), (int) (min_expiry - now),
                       (int)(max_expiry - now));
        else
            ap_rprintf(r, "expiry threshold: <b>Calculation Error!</b>"
                       "<br>");

    }
    ap_rprintf(r, "index usage: <b>%d%%</b>, cache usage: <b>%d%%</b>"
               "<br>", index_pct, cache_pct);
    ap_rprintf(r, "total sessions stored since starting: <b>%lu</b><br>",
               header->num_stores);
    ap_rprintf(r, "total sessions expired since starting: <b>%lu</b><br>",
               header->num_expiries);
    ap_rprintf(r, "total (pre-expiry) sessions scrolled out of the "
               "cache: <b>%lu</b><br>", header->num_scrolled);
    ap_rprintf(r, "total retrieves since starting: <b>%lu</b> hit, "
               "<b>%lu</b> miss<br>", header->num_retrieves_hit,
               header->num_retrieves_miss);
    ap_rprintf(r, "total removes since starting: <b>%lu</b> hit, "
               "<b>%lu</b> miss<br>", header->num_removes_hit,
               header->num_removes_miss);
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "leaving shmcb_status");
    return;
}

/*
**
** Memory manipulation and low-level cache operations
**
*/

static BOOL shmcb_init_memory(
    server_rec *s, void *shm_mem,
    unsigned int shm_mem_size)
{
    SHMCBHeader *header;
    SHMCBQueue queue;
    SHMCBCache cache;
    unsigned int temp, loop, granularity;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "entered shmcb_init_memory()");

    /* Calculate some sizes... */
    temp = sizeof(SHMCBHeader);

    /* If the segment is ridiculously too small, bail out */
    if (shm_mem_size < (2*temp)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "shared memory segment too small");
        return FALSE;
    }

    /* Make temp the amount of memory without the header */
    temp = shm_mem_size - temp;

    /* Work on the basis that you need 10 bytes index for each session
     * (approx 150 bytes), which is to divide temp by 160 - and then
     * make sure we err on having too index space to burn even when
     * the cache is full, which is a lot less stupid than having
     * having not enough index space to utilise the whole cache!. */
    temp /= 120;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "for %u bytes, recommending %u indexes",
                 shm_mem_size, temp);

    /* We should divide these indexes evenly amongst the queues. Try
     * to get it so that there are roughly half the number of divisions
     * as there are indexes in each division. */
    granularity = 256;
    while ((temp / granularity) < (2 * granularity))
        granularity /= 2;

    /* So we have 'granularity' divisions, set 'temp' equal to the
     * number of indexes in each division. */
    temp /= granularity;

    /* Too small? Bail ... */
    if (temp < 5) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "shared memory segment too small");
        return FALSE;
    }

    /* OK, we're sorted - from here on in, the return should be TRUE */
    header = (SHMCBHeader *)shm_mem;
    header->division_mask = (unsigned char)(granularity - 1);
    header->division_offset = sizeof(SHMCBHeader);
    header->index_num = temp;
    header->index_offset = (2 * sizeof(unsigned int));
    header->index_size = sizeof(SHMCBIndex);
    header->queue_size = header->index_offset +
                         (header->index_num * header->index_size);

    /* Now calculate the space for each division */
    temp = shm_mem_size - header->division_offset;
    header->division_size = temp / granularity;

    /* Calculate the space left in each division for the cache */
    temp -= header->queue_size;
    header->cache_data_offset = (2 * sizeof(unsigned int));
    header->cache_data_size = header->division_size -
                              header->queue_size - header->cache_data_offset;

    /* Output trace info */
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "shmcb_init_memory choices follow");
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "division_mask = 0x%02X", header->division_mask);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "division_offset = %u", header->division_offset);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "division_size = %u", header->division_size);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "queue_size = %u", header->queue_size);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "index_num = %u", header->index_num);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "index_offset = %u", header->index_offset);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "index_size = %u", header->index_size);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "cache_data_offset = %u", header->cache_data_offset);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "cache_data_size = %u", header->cache_data_size);

    /* The header is done, make the caches empty */
    for (loop = 0; loop < granularity; loop++) {
        if (!shmcb_get_division(header, &queue, &cache, loop))
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "shmcb_init_memory, " "internal error");
        shmcb_set_safe_uint(cache.first_pos, 0);
        shmcb_set_safe_uint(cache.pos_count, 0);
        shmcb_set_safe_uint(queue.first_pos, 0);
        shmcb_set_safe_uint(queue.pos_count, 0);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving shmcb_init_memory()");
    return TRUE;
}

static BOOL shmcb_store_session(
    server_rec *s, void *shm_segment, UCHAR *id,
    int idlen, SSL_SESSION * pSession,
    time_t timeout)
{
    SHMCBHeader *header;
    SHMCBQueue queue;
    SHMCBCache cache;
    unsigned char masked_index;
    unsigned char encoded[SSL_SESSION_MAX_DER];
    unsigned char *ptr_encoded;
    unsigned int len_encoded;
    time_t expiry_time;
    unsigned char *session_id = SSL_SESSION_get_session_id(pSession);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "inside shmcb_store_session");

    /* Get the header structure, which division this session will fall into etc. */
    shmcb_get_header(shm_segment, &header);
    masked_index = session_id[0] & header->division_mask;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "session_id[0]=%u, masked index=%u",
                 session_id[0], masked_index);
    if (!shmcb_get_division(header, &queue, &cache, (unsigned int)masked_index)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "shmcb_store_session internal error");
        return FALSE;
    }

    /* Serialise the session, work out how much we're dealing
     * with. NB: This check could be removed if we're not paranoid
     * or we find some assurance that it will never be necessary. */
    len_encoded = i2d_SSL_SESSION(pSession, NULL);
    if (len_encoded > SSL_SESSION_MAX_DER) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "session is too big (%u bytes)", len_encoded);
        return FALSE;
    }
    ptr_encoded = encoded;
    len_encoded = i2d_SSL_SESSION(pSession, &ptr_encoded);
    expiry_time = timeout;
    if (!shmcb_insert_encoded_session(s, &queue, &cache, encoded,
                                     len_encoded, session_id,
                                     expiry_time)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "can't store a session!");
        return FALSE;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving shmcb_store successfully");
    header->num_stores++;
    return TRUE;
}

static SSL_SESSION *shmcb_retrieve_session(
    server_rec *s, void *shm_segment,
    UCHAR *id, int idlen)
{
    SHMCBHeader *header;
    SHMCBQueue queue;
    SHMCBCache cache;
    unsigned char masked_index;
    SSL_SESSION *pSession;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "inside shmcb_retrieve_session");
    if (idlen < 2) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "unusably short session_id provided "
                "(%u bytes)", idlen);
        return FALSE;
    }

    /* Get the header structure, which division this session lookup
     * will come from etc. */
    shmcb_get_header(shm_segment, &header);
    masked_index = id[0] & header->division_mask;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "id[0]=%u, masked index=%u", id[0], masked_index);
    if (!shmcb_get_division(header, &queue, &cache, (unsigned int) masked_index)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "shmcb_retrieve_session internal error");
        header->num_retrieves_miss++;
        return FALSE;
    }

    /* Get the session corresponding to the session_id or NULL if it
     * doesn't exist (or is flagged as "removed"). */
    pSession = shmcb_lookup_session_id(s, &queue, &cache, id, idlen);
    if (pSession)
        header->num_retrieves_hit++;
    else
        header->num_retrieves_miss++;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving shmcb_retrieve_session");
    return pSession;
}

static BOOL shmcb_remove_session(
    server_rec *s, void *shm_segment,
    UCHAR *id, int idlen)
{
    SHMCBHeader *header;
    SHMCBQueue queue;
    SHMCBCache cache;
    unsigned char masked_index;
    BOOL res;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "inside shmcb_remove_session");
    if (id == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "remove called with NULL session_id!");
        return FALSE;
    }

    /* Get the header structure, which division this session remove
     * will happen in etc. */
    shmcb_get_header(shm_segment, &header);
    masked_index = id[0] & header->division_mask;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "id[0]=%u, masked index=%u", id[0], masked_index);
    if (!shmcb_get_division(header, &queue, &cache, (unsigned int)masked_index)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "shmcb_remove_session, internal error");
        header->num_removes_miss++;
        return FALSE;
    }
    res = shmcb_remove_session_id(s, &queue, &cache, id, idlen);
    if (res)
        header->num_removes_hit++;
    else
        header->num_removes_miss++;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving shmcb_remove_session");
    return res;
}


/*
**
** Weirdo cyclic buffer functions
**
*/

/* This gets used in the cyclic "index array" (in the 'Queue's) and
 * in the cyclic 'Cache's too ... you provide the "width" of the
 * cyclic store, the starting position and how far to move (with
 * wrapping if necessary). Basically it's addition modulo buf_size. */
static unsigned int shmcb_cyclic_increment(
    unsigned int buf_size,
    unsigned int start_pos,
    unsigned int to_add)
{
    start_pos += to_add;
    while (start_pos >= buf_size)
        start_pos -= buf_size;
    return start_pos;
}

/* Given two positions in a cyclic buffer, calculate the "distance".
 * This is to cover the case ("non-trivial") where the 'next' offset
 * is to the left of the 'start' offset. NB: This calculates the
 * space inclusive of one end-point but not the other. There is an
 * ambiguous case (which is why we use the <start_pos,offset>
 * coordinate system rather than <start_pos,end_pos> one) when 'start'
 * is the same as 'next'. It could indicate the buffer is full or it
 * can indicate the buffer is empty ... I choose the latter as it's
 * easier and usually necessary to check if the buffer is full anyway
 * before doing incremental logic (which is this useful for), but we
 * definitely need the empty case handled - in fact it's our starting
 * state!! */
static unsigned int shmcb_cyclic_space(
    unsigned int buf_size,
    unsigned int start_offset,
    unsigned int next_offset)
{
    /* Is it the trivial case? */
    if (start_offset <= next_offset)
        return (next_offset - start_offset);              /* yes */
    else
        return ((buf_size - start_offset) + next_offset); /* no */
}

/* A "normal-to-cyclic" memcpy ... this takes a linear block of
 * memory and copies it onto a cyclic buffer. The purpose and
 * function of this is pretty obvious, you need to cover the case
 * that the destination (cyclic) buffer has to wrap round. */
static void shmcb_cyclic_ntoc_memcpy(
    unsigned int buf_size,
    unsigned char *data,
    unsigned int dest_offset,
    unsigned char *src, unsigned int src_len)
{
    /* Cover the case that src_len > buf_size */
    if (src_len > buf_size)
        src_len = buf_size;

    /* Can it be copied all in one go? */
    if (dest_offset + src_len < buf_size)
        /* yes */
        memcpy(data + dest_offset, src, src_len);
    else {
        /* no */
        memcpy(data + dest_offset, src, buf_size - dest_offset);
        memcpy(data, src + buf_size - dest_offset,
               src_len + dest_offset - buf_size);
    }
    return;
}

/* A "cyclic-to-normal" memcpy ... given the last function, this
 * one's purpose is clear, it copies out of a cyclic buffer handling
 * wrapping. */
static void shmcb_cyclic_cton_memcpy(
    unsigned int buf_size,
    unsigned char *dest,
    unsigned char *data,
    unsigned int src_offset,
    unsigned int src_len)
{
    /* Cover the case that src_len > buf_size */
    if (src_len > buf_size)
        src_len = buf_size;

    /* Can it be copied all in one go? */
    if (src_offset + src_len < buf_size)
        /* yes */
        memcpy(dest, data + src_offset, src_len);
    else {
        /* no */
        memcpy(dest, data + src_offset, buf_size - src_offset);
        memcpy(dest + buf_size - src_offset, data,
               src_len + src_offset - buf_size);
    }
    return;
}

/* Here's the cool hack that makes it all work ... by simply
 * making the first collection of bytes *be* our header structure
 * (casting it into the C structure), we have the perfect way to
 * maintain state in a shared-memory session cache from one call
 * (and process) to the next, use the shared memory itself! The
 * original mod_ssl shared-memory session cache uses variables
 * inside the context, but we simply use that for storing the
 * pointer to the shared memory itself. And don't forget, after
 * Apache's initialisation, this "header" is constant/read-only
 * so we can read it outside any locking.
 * <grin> - sometimes I just *love* coding y'know?!  */
static void shmcb_get_header(void *shm_mem, SHMCBHeader **header)
{
    *header = (SHMCBHeader *)shm_mem;
    return;
}

/* This is what populates our "interesting" structures. Given a
 * pointer to the header, and an index into the appropriate
 * division (this must have already been masked using the
 * division_mask by the caller!), we can populate the provided
 * SHMCBQueue and SHMCBCache structures with values and
 * pointers to the underlying shared memory. Upon returning
 * (if not FALSE), the caller can meddle with the pointer
 * values and they will map into the shared-memory directly,
 * as such there's no need to "free" or "set" the Queue or
 * Cache values, they were themselves references to the *real*
 * data. */
static BOOL shmcb_get_division(
    SHMCBHeader *header, SHMCBQueue *queue,
    SHMCBCache *cache, unsigned int idx)
{
    unsigned char *pQueue;
    unsigned char *pCache;

    /* bounds check */
    if (idx > (unsigned int) header->division_mask)
        return FALSE;

    /* Locate the blocks of memory storing the corresponding data */
    pQueue = ((unsigned char *) header) + header->division_offset +
        (idx * header->division_size);
    pCache = pQueue + header->queue_size;

    /* Populate the structures with appropriate pointers */
    queue->first_pos = (unsigned int *) pQueue;

    /* Our structures stay packed, no matter what the system's
     * data-alignment regime is. */
    queue->pos_count = (unsigned int *) (pQueue + sizeof(unsigned int));
    queue->indexes = (SHMCBIndex *) (pQueue + (2 * sizeof(unsigned int)));
    cache->first_pos = (unsigned int *) pCache;
    cache->pos_count = (unsigned int *) (pCache + sizeof(unsigned int));
    cache->data = (unsigned char *) (pCache + (2 * sizeof(unsigned int)));
    queue->header = cache->header = header;

    return TRUE;
}

/* This returns a pointer to the piece of shared memory containing
 * a specified 'Index'. SHMCBIndex, like SHMCBHeader, is a fixed
 * width non-referencing structure of primitive types that can be
 * cast onto the corresponding block of shared memory. Thus, by
 * returning a cast pointer to that section of shared memory, the
 * caller can read and write values to and from the "structure" and
 * they are actually reading and writing the underlying shared
 * memory. */
static SHMCBIndex *shmcb_get_index(
    const SHMCBQueue *queue, unsigned int idx)
{
    /* bounds check */
    if (idx > queue->header->index_num)
        return NULL;

    /* Return a pointer to the index. NB: I am being horribly pendantic
     * here so as to avoid any potential data-alignment assumptions being
     * placed on the pointer arithmetic by the compiler (sigh). */
    return (SHMCBIndex *)(((unsigned char *) queue->indexes) +
                          (idx * sizeof(SHMCBIndex)));
}

/* This functions rolls expired cache (and index) entries off the front
 * of the cyclic buffers in a division. The function returns the number
 * of expired sessions. */
static unsigned int shmcb_expire_division(
    server_rec *s, SHMCBQueue *queue, SHMCBCache *cache)
{
    SHMCBIndex *idx;
    time_t now;
    unsigned int loop, index_num, pos_count, new_pos;
    SHMCBHeader *header;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "entering shmcb_expire_division");

    /* We must calculate num and space ourselves based on expiry times. */
    now = time(NULL);
    loop = 0;
    new_pos = shmcb_get_safe_uint(queue->first_pos);

    /* Cache useful values */
    header = queue->header;
    index_num = header->index_num;
    pos_count = shmcb_get_safe_uint(queue->pos_count);
    while (loop < pos_count) {
        idx = shmcb_get_index(queue, new_pos);
        if (shmcb_get_safe_time(&(idx->expires)) > now)
            /* it hasn't expired yet, we're done iterating */
            break;
        /* This one should be expired too. Shift to the next entry. */
        loop++;
        new_pos = shmcb_cyclic_increment(index_num, new_pos, 1);
    }

    /* Find the new_offset and make the expiries happen. */
    if (loop > 0) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "will be expiring %u sessions", loop);
        /* We calculate the new_offset by "peeking" (or in the
         * case it's the last entry, "sneaking" ;-). */
        if (loop == pos_count) {
            /* We are expiring everything! This is easy to do... */
            shmcb_set_safe_uint(queue->pos_count, 0);
            shmcb_set_safe_uint(cache->pos_count, 0);
        }
        else {
            /* The Queue is easy to adjust */
            shmcb_set_safe_uint(queue->pos_count,
                               shmcb_get_safe_uint(queue->pos_count) - loop);
            shmcb_set_safe_uint(queue->first_pos, new_pos);
            /* peek to the start of the next session */
            idx = shmcb_get_index(queue, new_pos);
            /* We can use shmcb_cyclic_space because we've guaranteed
             * we don't fit the ambiguous full/empty case. */
            shmcb_set_safe_uint(cache->pos_count,
                               shmcb_get_safe_uint(cache->pos_count) -
                               shmcb_cyclic_space(header->cache_data_size,
                                                  shmcb_get_safe_uint(cache->first_pos),
                                                  shmcb_get_safe_uint(&(idx->offset))));
            shmcb_set_safe_uint(cache->first_pos, shmcb_get_safe_uint(&(idx->offset)));
        }
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "we now have %u sessions",
                     shmcb_get_safe_uint(queue->pos_count));
    }
    header->num_expiries += loop;
    return loop;
}

/* Inserts a new encoded session into a queue/cache pair - expiring
 * (early or otherwise) any leading sessions as necessary to ensure
 * there is room. An error return (FALSE) should only happen in the
 * event of surreal values being passed on, or ridiculously small
 * cache sizes. NB: For tracing purposes, this function is also given
 * the server_rec to allow "ssl_log()". */
static BOOL shmcb_insert_encoded_session(
    server_rec *s, SHMCBQueue * queue,
    SHMCBCache * cache,
    unsigned char *encoded,
    unsigned int encoded_len,
    unsigned char *session_id,
    time_t expiry_time)
{
    SHMCBHeader *header;
    SHMCBIndex *idx = NULL;
    unsigned int gap, new_pos, loop, new_offset;
    int need;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "entering shmcb_insert_encoded_session, "
                 "*queue->pos_count = %u",
                 shmcb_get_safe_uint(queue->pos_count));

    /* If there's entries to expire, ditch them first thing. */
    shmcb_expire_division(s, queue, cache);
    header = cache->header;
    gap = header->cache_data_size - shmcb_get_safe_uint(cache->pos_count);
    if (gap < encoded_len) {
        new_pos = shmcb_get_safe_uint(queue->first_pos);
        loop = 0;
        need = (int) encoded_len - (int) gap;
        while ((need > 0) && (loop + 1 < shmcb_get_safe_uint(queue->pos_count))) {
            new_pos = shmcb_cyclic_increment(header->index_num, new_pos, 1);
            loop += 1;
            idx = shmcb_get_index(queue, new_pos);
            need = (int) encoded_len - (int) gap -
                shmcb_cyclic_space(header->cache_data_size,
                                   shmcb_get_safe_uint(cache->first_pos),
                                   shmcb_get_safe_uint(&(idx->offset)));
        }
        if (loop > 0) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "about to scroll %u sessions from %u",
                         loop, shmcb_get_safe_uint(queue->pos_count));
            /* We are removing "loop" items from the cache. */
            shmcb_set_safe_uint(cache->pos_count,
                                shmcb_get_safe_uint(cache->pos_count) -
                                shmcb_cyclic_space(header->cache_data_size,
                                                   shmcb_get_safe_uint(cache->first_pos),
                                                   shmcb_get_safe_uint(&(idx->offset))));
            shmcb_set_safe_uint(cache->first_pos, shmcb_get_safe_uint(&(idx->offset)));
            shmcb_set_safe_uint(queue->pos_count, shmcb_get_safe_uint(queue->pos_count) - loop);
            shmcb_set_safe_uint(queue->first_pos, new_pos);
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "now only have %u sessions",
                         shmcb_get_safe_uint(queue->pos_count));
            /* Update the stats!!! */
            header->num_scrolled += loop;
        }
    }

    /* probably unecessary checks, but I'll leave them until this code
     * is verified. */
    if (shmcb_get_safe_uint(cache->pos_count) + encoded_len >
        header->cache_data_size) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "shmcb_insert_encoded_session internal error");
        return FALSE;
    }
    if (shmcb_get_safe_uint(queue->pos_count) == header->index_num) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "shmcb_insert_encoded_session internal error");
        return FALSE;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "we have %u bytes and %u indexes free - enough",
                 header->cache_data_size -
                 shmcb_get_safe_uint(cache->pos_count), header->index_num -
                 shmcb_get_safe_uint(queue->pos_count));


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

    /* Increment to the first unused byte */
    new_offset = shmcb_cyclic_increment(header->cache_data_size,
                                        shmcb_get_safe_uint(cache->first_pos),
                                        shmcb_get_safe_uint(cache->pos_count));
    /* Copy the DER-encoded session into place */
    shmcb_cyclic_ntoc_memcpy(header->cache_data_size, cache->data,
                            new_offset, encoded, encoded_len);
    /* Get the new index that this session is stored in. */
    new_pos = shmcb_cyclic_increment(header->index_num,
                                     shmcb_get_safe_uint(queue->first_pos),
                                     shmcb_get_safe_uint(queue->pos_count));
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "storing in index %u, at offset %u",
                 new_pos, new_offset);
    idx = shmcb_get_index(queue, new_pos);
    if (idx == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "shmcb_insert_encoded_session internal error");
        return FALSE;
    }
    shmcb_safe_clear(idx, sizeof(SHMCBIndex));
    shmcb_set_safe_time(&(idx->expires), expiry_time);
    shmcb_set_safe_uint(&(idx->offset), new_offset);

    /* idx->removed = (unsigned char)0; */ /* Not needed given the memset above. */
    idx->s_id2 = session_id[1];
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "session_id[0]=%u, idx->s_id2=%u",
                 session_id[0], session_id[1]);

    /* All that remains is to adjust the cache's and queue's "pos_count"s. */
    shmcb_set_safe_uint(cache->pos_count,
                       shmcb_get_safe_uint(cache->pos_count) + encoded_len);
    shmcb_set_safe_uint(queue->pos_count,
                       shmcb_get_safe_uint(queue->pos_count) + 1);

    /* And just for good debugging measure ... */
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving now with %u bytes in the cache and %u indexes",
                 shmcb_get_safe_uint(cache->pos_count),
                 shmcb_get_safe_uint(queue->pos_count));
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving shmcb_insert_encoded_session");
    return TRUE;
}

/* Performs a lookup into a queue/cache pair for a
 * session_id. If found, the session is deserialised
 * and returned, otherwise NULL. */
static SSL_SESSION *shmcb_lookup_session_id(
    server_rec *s, SHMCBQueue *queue,
    SHMCBCache *cache, UCHAR *id,
    unsigned int idlen)
{
    unsigned char tempasn[SSL_SESSION_MAX_DER];
    SHMCBIndex *idx;
    SHMCBHeader *header;
    SSL_SESSION *pSession = NULL;
    unsigned int curr_pos, loop, count;
    MODSSL_D2I_SSL_SESSION_CONST unsigned char *ptr;
    time_t now;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "entering shmcb_lookup_session_id");

    /* If there are entries to expire, ditch them first thing. */
    shmcb_expire_division(s, queue, cache);
    now = time(NULL);
    curr_pos = shmcb_get_safe_uint(queue->first_pos);
    count = shmcb_get_safe_uint(queue->pos_count);
    header = queue->header;
    for (loop = 0; loop < count; loop++) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "loop=%u, count=%u, curr_pos=%u",
                     loop, count, curr_pos);
        idx = shmcb_get_index(queue, curr_pos);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "idx->s_id2=%u, id[1]=%u, offset=%u",
                idx->s_id2, id[1], shmcb_get_safe_uint(&(idx->offset)));
        /* Only look into the session further if;
         * (a) the second byte of the session_id matches,
         * (b) the "removed" flag isn't set,
         * (c) the session hasn't expired yet.
         * We do (c) like this so that it saves us having to
         * do natural expiries ... naturally expired sessions
         * scroll off the front anyway when the cache is full and
         * "rotating", the only real issue that remains is the
         * removal or disabling of forcibly killed sessions. */
        if ((idx->s_id2 == id[1]) && !idx->removed &&
            (shmcb_get_safe_time(&(idx->expires)) > now)) {
            unsigned int session_id_length;
            unsigned char *session_id;

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "at index %u, found possible session match",
                         curr_pos);
            shmcb_cyclic_cton_memcpy(header->cache_data_size,
                                     tempasn, cache->data,
                                     shmcb_get_safe_uint(&(idx->offset)),
                                     SSL_SESSION_MAX_DER);
            ptr = tempasn;
            pSession = d2i_SSL_SESSION(NULL, &ptr, SSL_SESSION_MAX_DER);
            session_id_length = SSL_SESSION_get_session_id_length(pSession);
            session_id = SSL_SESSION_get_session_id(pSession);

            if (pSession == NULL) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                             "scach2_lookup_session_id internal error");
                return NULL;
            }
            if ((session_id_length == idlen) &&
                (memcmp(session_id, id, idlen) == 0)) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                             "a match!");
                return pSession;
            }
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "not a match");
            SSL_SESSION_free(pSession);
            pSession = NULL;
        }
        curr_pos = shmcb_cyclic_increment(header->index_num, curr_pos, 1);
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "no matching sessions were found");
    return NULL;
}

static BOOL shmcb_remove_session_id(
    server_rec *s, SHMCBQueue *queue,
    SHMCBCache *cache, UCHAR *id, unsigned int idlen)
{
    unsigned char tempasn[SSL_SESSION_MAX_DER];
    SSL_SESSION *pSession = NULL;
    SHMCBIndex *idx;
    SHMCBHeader *header;
    unsigned int curr_pos, loop, count;
    MODSSL_D2I_SSL_SESSION_CONST unsigned char *ptr;
    BOOL to_return = FALSE;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "entering shmcb_remove_session_id");

    /* If there's entries to expire, ditch them first thing. */
    /* shmcb_expire_division(s, queue, cache); */

    /* Regarding the above ... hmmm ... I know my expiry code is slightly
     * "faster" than all this remove stuff ... but if the higher level
     * code calls a "remove" operation (and this *only* seems to happen
     * when it has spotted an expired session before we had a chance to)
     * then it should get credit for a remove (stats-wise). Also, in the
     * off-chance that the server *requests* a renegotiate and wants to
     * wipe the session clean we should give that priority over our own
     * routine expiry handling. So I've moved the expiry check to *after*
     * this general remove stuff. */
    curr_pos = shmcb_get_safe_uint(queue->first_pos);
    count = shmcb_get_safe_uint(queue->pos_count);
    header = cache->header;
    for (loop = 0; loop < count; loop++) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "loop=%u, count=%u, curr_pos=%u",
                loop, count, curr_pos);
        idx = shmcb_get_index(queue, curr_pos);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "idx->s_id2=%u, id[1]=%u", idx->s_id2,
                id[1]);
        /* Only look into the session further if the second byte of the
         * session_id matches. */
        if (idx->s_id2 == id[1]) {
            unsigned int session_id_length;
            unsigned char *session_id;

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "at index %u, found possible "
                         "session match", curr_pos);
            shmcb_cyclic_cton_memcpy(header->cache_data_size,
                                     tempasn, cache->data,
                                     shmcb_get_safe_uint(&(idx->offset)),
                                     SSL_SESSION_MAX_DER);
            ptr = tempasn;
            pSession = d2i_SSL_SESSION(NULL, &ptr, SSL_SESSION_MAX_DER);
            if (pSession == NULL) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                             "shmcb_remove_session_id, internal error");
                goto end;
            }
            session_id_length = SSL_SESSION_get_session_id_length(pSession);
            session_id = SSL_SESSION_get_session_id(pSession);

            if ((session_id_length == idlen)
                 && (memcmp(id, session_id, idlen) == 0)) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                            "a match!");
                /* Scrub out this session "quietly" */
                idx->removed = (unsigned char) 1;
                SSL_SESSION_free(pSession);
                to_return = TRUE;
                goto end;
            }
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "not a match");
            SSL_SESSION_free(pSession);
            pSession = NULL;
        }
        curr_pos = shmcb_cyclic_increment(header->index_num, curr_pos, 1);
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "no matching sessions were found");

    /* If there's entries to expire, ditch them now. */
    shmcb_expire_division(s, queue, cache);
end:
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving shmcb_remove_session_id");
    return to_return;
}

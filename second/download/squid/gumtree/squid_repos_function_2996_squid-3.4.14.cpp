static void
wccpAssignBuckets(void)
{

    struct wccp_assign_bucket_t *wccp_assign_bucket;
    int wab_len;
    char *buckets;
    int buckets_per_cache;
    unsigned int loop;
    int bucket = 0;
    int *caches;
    int cache_len;
    char *buf;

    debugs(80, 6, "wccpAssignBuckets: Called");
    number_caches = ntohl(wccp_i_see_you.number);

    assert(number_caches > 0);
    assert(number_caches <= WCCP_ACTIVE_CACHES);

    wab_len = sizeof(struct wccp_assign_bucket_t);

    cache_len = WCCP_CACHE_LEN * number_caches;

    buf = (char *)xmalloc(wab_len +
                          WCCP_BUCKETS +
                          cache_len);

    wccp_assign_bucket = (struct wccp_assign_bucket_t *) buf;

    caches = (int *) (buf + wab_len);

    buckets = buf + wab_len + cache_len;

    memset(wccp_assign_bucket, '\0', sizeof(*wccp_assign_bucket));

    memset(buckets, 0xFF, WCCP_BUCKETS);

    buckets_per_cache = WCCP_BUCKETS / number_caches;

    for (loop = 0; loop < number_caches; ++loop) {
        int i;
        memcpy(&caches[loop],
               &wccp_i_see_you.wccp_cache_entry[loop].ip_addr,
               sizeof(*caches));

        for (i = 0; i < buckets_per_cache; ++i) {
            assert(bucket < WCCP_BUCKETS);
            buckets[bucket] = loop;
            ++bucket;
        }
    }

    while (bucket < WCCP_BUCKETS) {
        buckets[bucket] = number_caches - 1;
        ++bucket;
    }

    wccp_assign_bucket->type = htonl(WCCP_ASSIGN_BUCKET);
    wccp_assign_bucket->id = wccp_i_see_you.id;
    wccp_assign_bucket->number = wccp_i_see_you.number;

    comm_udp_send(theWccpConnection,
                  buf,
                  wab_len + WCCP_BUCKETS + cache_len,
                  0);
    last_change = 0;
    xfree(buf);
}
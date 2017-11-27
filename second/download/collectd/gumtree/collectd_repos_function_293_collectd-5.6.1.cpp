static int32_t kafka_partition(const rd_kafka_topic_t *rkt,
                               const void *keydata, size_t keylen,
                               int32_t partition_cnt, void *p, void *m)
{
    uint32_t key = kafka_hash(keydata, keylen);
    uint32_t target = key % partition_cnt;
    int32_t  i = partition_cnt;

    while (--i > 0 && !rd_kafka_topic_partition_available(rkt, target)) {
        target = (target + 1) % partition_cnt;
    }
    return target;
}
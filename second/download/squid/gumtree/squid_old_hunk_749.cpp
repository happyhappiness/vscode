    storeAppendPrintf(e, "\t bit-seq: count: %d avg.len: %.2f\n",
                      stats.bseq_count,
                      xdiv(stats.bseq_len_sum, stats.bseq_count)
                     );
}

size_t
cacheDigestCalcMaskSize(int cap, int bpe)
{
    return (size_t) (cap * bpe + 7) / 8;
}

static void
cacheDigestHashKey(const CacheDigest * cd, const cache_key * key)
{
    const unsigned int bit_count = cd->mask_size * 8;
    unsigned int tmp_keys[4];
    /* we must memcpy to ensure alignment */
    memcpy(tmp_keys, key, sizeof(tmp_keys));
    hashed_keys[0] = htonl(tmp_keys[0]) % bit_count;
    hashed_keys[1] = htonl(tmp_keys[1]) % bit_count;
    hashed_keys[2] = htonl(tmp_keys[2]) % bit_count;

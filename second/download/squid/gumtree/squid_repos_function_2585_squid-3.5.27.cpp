static void
cacheDigestStats(const CacheDigest * cd, CacheDigestStats * stats)
{
    int on_count = 0;
    int pos = cd->mask_size * 8;
    int seq_len_sum = 0;
    int seq_count = 0;
    int cur_seq_len = 0;
    int cur_seq_type = 1;
    assert(stats);
    memset(stats, 0, sizeof(*stats));

    while (pos-- > 0) {
        const int is_on = 0 != CBIT_TEST(cd->mask, pos);

        if (is_on)
            ++on_count;

        if (is_on != cur_seq_type || !pos) {
            seq_len_sum += cur_seq_len;
            ++seq_count;
            cur_seq_type = is_on;
            cur_seq_len = 0;
        }

        ++cur_seq_len;
    }

    stats->bit_count = cd->mask_size * 8;
    stats->bit_on_count = on_count;
    stats->bseq_len_sum = seq_len_sum;
    stats->bseq_count = seq_count;
}
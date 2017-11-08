static void dump_iphash_statistics(server_rec *main_s)
{
    unsigned count[IPHASH_TABLE_SIZE];
    int i;
    ipaddr_chain *src;
    unsigned total;
    char buf[HUGE_STRING_LEN];
    char *p;

    total = 0;
    for (i = 0; i < IPHASH_TABLE_SIZE; ++i) {
        count[i] = 0;
        for (src = iphash_table[i]; src; src = src->next) {
            ++count[i];
            if (i < IPHASH_TABLE_SIZE) {
                /* don't count the slop buckets in the total */
                ++total;
            }
        }
    }
    qsort(count, IPHASH_TABLE_SIZE, sizeof(count[0]), iphash_compare);
    p = buf + apr_snprintf(buf, sizeof(buf),
                           "iphash: total hashed = %u, avg chain = %u, "
                           "chain lengths (count x len):",
                           total, total / IPHASH_TABLE_SIZE);
    total = 1;
    for (i = 1; i < IPHASH_TABLE_SIZE; ++i) {
        if (count[i - 1] != count[i]) {
            p += apr_snprintf(p, sizeof(buf) - (p - buf), " %ux%u",
                              total, count[i - 1]);
            total = 1;
        }
        else {
            ++total;
        }
    }
    p += apr_snprintf(p, sizeof(buf) - (p - buf), " %ux%u",
                      total, count[IPHASH_TABLE_SIZE - 1]);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, main_s, buf);
}
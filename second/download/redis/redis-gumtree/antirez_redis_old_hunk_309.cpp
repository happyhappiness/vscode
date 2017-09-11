/* Generates a key name among a set of lru_test_sample_size keys, using
 * an 80-20 distribution. */
void LRUTestGenKey(char *buf, size_t buflen) {
    snprintf(buf, buflen, "lru:%lld\n",
        powerLawRand(1, config.lru_test_sample_size, 6.2));
}


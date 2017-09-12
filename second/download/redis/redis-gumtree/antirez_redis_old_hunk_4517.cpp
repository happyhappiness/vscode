
#define DICT_STATS_VECTLEN 50
void dictPrintStats(dict *ht) {
    unsigned int i, slots = 0, chainlen, maxchainlen = 0;
    unsigned int totchainlen = 0;
    unsigned int clvector[DICT_STATS_VECTLEN];

    if (ht->used == 0) {
        printf("No stats available for empty dictionaries\n");

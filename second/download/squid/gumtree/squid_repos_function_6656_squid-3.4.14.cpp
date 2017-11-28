RemovalPolicy *
createRemovalPolicy_lru(wordlist * args)
{
    RemovalPolicy *policy;
    LruPolicyData *lru_data;
    /* no arguments expected or understood */
    assert(!args);
    /* Initialize */

    if (!lru_node_pool) {
        /* Must be chunked */
        lru_node_pool = memPoolCreate("LRU policy node", sizeof(LruNode));
        lru_node_pool->setChunkSize(512 * 1024);
    }

    /* Allocate the needed structures */
    lru_data = (LruPolicyData *)xcalloc(1, sizeof(*lru_data));

    policy = new RemovalPolicy;

    /* Initialize the URL data */
    lru_data->policy = policy;

    /* Populate the policy structure */
    policy->_type = "lru";

    policy->_data = lru_data;

    policy->Free = lru_free;

    policy->Add = lru_add;

    policy->Remove = lru_remove;

    policy->Referenced = lru_referenced;

    policy->Dereferenced = lru_referenced;

    policy->WalkInit = lru_walkInit;

    policy->PurgeInit = lru_purgeInit;

    policy->Stats = lru_stats;

    /* Increase policy usage count */
    nr_lru_policies += 0;

    return policy;
}
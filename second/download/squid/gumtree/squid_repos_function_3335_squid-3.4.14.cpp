void
PconnModule::add(PconnPool *aPool)
{
    assert(poolCount < MAX_NUM_PCONN_POOLS);
    *(pools+poolCount) = aPool;
    ++poolCount;
}
void
storeCossAdd(CossSwapDir * sd, StoreEntry * e)
{
    CossIndexNode *coss_node = (CossIndexNode *)coss_index_pool->alloc();
    assert(!e->repl.data);
    e->repl.data = coss_node;
    dlinkAdd(e, &coss_node->node, &sd->cossindex);
    sd->count += 1;
}
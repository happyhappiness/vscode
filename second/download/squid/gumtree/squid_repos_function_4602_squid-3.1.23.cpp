void
storeCossRemove(CossSwapDir * sd, StoreEntry * e)
{
    CossIndexNode *coss_node = (CossIndexNode *)e->repl.data;
    e->repl.data = NULL;
    dlinkDelete(&coss_node->node, &sd->cossindex);
    coss_index_pool->free(coss_node);
    sd->count -= 1;
}
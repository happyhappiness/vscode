void
UFSSwapDir::replacementAdd(StoreEntry * e)
{
    debugs(47, 4, "UFSSwapDir::replacementAdd: added node " << e << " to dir " << index);
    repl->Add(repl, e, &e->repl);
}
void
Fs::Ufs::UFSSwapDir::replacementAdd(StoreEntry * e)
{
    debugs(47, 4, HERE << "added node " << e << " to dir " << index);
    repl->Add(repl, e, &e->repl);
}
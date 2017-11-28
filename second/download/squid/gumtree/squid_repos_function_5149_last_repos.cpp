void
Fs::Ufs::UFSSwapDir::replacementRemove(StoreEntry * e)
{
    if (e->swap_dirn < 0)
        return;

    SwapDirPointer SD = INDEXSD(e->swap_dirn);

    assert (dynamic_cast<UFSSwapDir *>(SD.getRaw()) == this);

    debugs(47, 4, HERE << "remove node " << e << " from dir " << index);

    repl->Remove(repl, e, &e->repl);
}
void
UFSSwapDir::replacementRemove(StoreEntry * e)
{
    StorePointer SD;

    if (e->swap_dirn < 0)
        return;

    SD = INDEXSD(e->swap_dirn);

    assert (dynamic_cast<UFSSwapDir *>(SD.getRaw()) == this);

    debugs(47, 4, "UFSSwapDir::replacementRemove: remove node " << e << " from dir " << index);

    repl->Remove(repl, e, &e->repl);
}
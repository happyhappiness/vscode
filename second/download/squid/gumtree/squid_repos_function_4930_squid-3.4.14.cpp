void
Rock::SwapDir::ignoreReferences(StoreEntry &e)
{
    debugs(47, 5, HERE << e);
    if (repl)
        repl->Remove(repl, &e, &e.repl);
}
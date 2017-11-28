void
Rock::SwapDir::trackReferences(StoreEntry &e)
{
    debugs(47, 5, HERE << e);
    if (repl)
        repl->Add(repl, &e, &e.repl);
}
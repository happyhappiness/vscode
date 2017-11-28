bool
Rock::SwapDir::dereference(StoreEntry &e)
{
    debugs(47, 5, HERE << &e << ' ' << e.swap_dirn << ' ' << e.swap_filen);
    if (repl && repl->Dereferenced)
        repl->Dereferenced(repl, &e, &e.repl);

    // no need to keep e in the global store_table for us; we have our own map
    return false;
}
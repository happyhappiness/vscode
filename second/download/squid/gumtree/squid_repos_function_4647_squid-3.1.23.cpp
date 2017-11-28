void
UFSSwapDir::dereference(StoreEntry & e)
{
    debugs(47, 3, "UFSSwapDir::dereference: referencing " << &e << " " << e.swap_dirn << "/" << e.swap_filen);

    if (repl->Dereferenced)
        repl->Dereferenced(repl, &e, &e.repl);
}
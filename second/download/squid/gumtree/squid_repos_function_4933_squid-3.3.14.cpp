bool
Fs::Ufs::UFSSwapDir::dereference(StoreEntry & e, bool)
{
    debugs(47, 3, HERE << "dereferencing " << &e << " " <<
           e.swap_dirn << "/" << e.swap_filen);

    if (repl->Dereferenced)
        repl->Dereferenced(repl, &e, &e.repl);

    return true; // keep e in the global store_table
}
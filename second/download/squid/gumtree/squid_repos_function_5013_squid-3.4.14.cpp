void
Fs::Ufs::UFSSwapDir::reference(StoreEntry &e)
{
    debugs(47, 3, HERE << "referencing " << &e << " " <<
           e.swap_dirn << "/" << e.swap_filen);

    if (repl->Referenced)
        repl->Referenced(repl, &e, &e.repl);
}
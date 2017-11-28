void
Fs::Ufs::UFSStoreState::freePending()
{
    while (!pending_reads.empty())
        pending_reads.pop();
    debugs(79, 3, "freed pending reads");

    while (!pending_writes.empty())
        pending_writes.pop();
    debugs(79, 3, "freed pending writes");
}
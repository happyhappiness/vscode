void
MemStoreClaimMemoryNeedsRr::run(const RunnerRegistry &)
{
    Ipc::Mem::NotePageNeed(Ipc::Mem::PageId::cachePage, MemStore::EntryLimit());
}
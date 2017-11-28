void
MemStoreRr::claimMemoryNeeds()
{
    Ipc::Mem::NotePageNeed(Ipc::Mem::PageId::cachePage, MemStore::EntryLimit());
}
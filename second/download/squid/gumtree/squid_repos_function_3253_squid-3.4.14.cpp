bool
MemStore::copyToShm(StoreEntry &e, MemStoreMap::Extras &extras)
{
    Ipc::Mem::PageId page;
    if (!Ipc::Mem::GetPage(Ipc::Mem::PageId::cachePage, page)) {
        debugs(20, 5, HERE << "No mem-cache page for " << e);
        return false; // GetPage is responsible for any cleanup on failures
    }

    const int64_t bufSize = Ipc::Mem::PageSize();
    const int64_t eSize = e.mem_obj->endOffset();

    StoreIOBuffer sharedSpace(bufSize, 0,
                              static_cast<char*>(PagePointer(page)));

    // check that we kept everything or purge incomplete/sparse cached entry
    const ssize_t copied = e.mem_obj->data_hdr.copy(sharedSpace);
    if (eSize != copied) {
        debugs(20, 2, HERE << "Failed to mem-cache " << e << ": " <<
               eSize << "!=" << copied);
        // cleanup
        PutPage(page);
        return false;
    }

    debugs(20, 7, HERE << "mem-cached all " << eSize << " bytes of " << e <<
           " in " << page);

    theCurrentSize += Ipc::Mem::PageSize();
    // remember storage location and size
    extras.page = page;
    extras.storedSize = copied;
    return true;
}
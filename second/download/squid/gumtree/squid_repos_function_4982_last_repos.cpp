void Rock::SwapDirRr::create()
{
    Must(mapOwners.empty() && freeSlotsOwners.empty());
    for (int i = 0; i < Config.cacheSwap.n_configured; ++i) {
        if (const Rock::SwapDir *const sd = dynamic_cast<Rock::SwapDir *>(INDEXSD(i))) {
            const int64_t capacity = sd->slotLimitActual();

            SwapDir::DirMap::Owner *const mapOwner =
                SwapDir::DirMap::Init(sd->inodeMapPath(), capacity);
            mapOwners.push_back(mapOwner);

            // TODO: somehow remove pool id and counters from PageStack?
            Ipc::Mem::Owner<Ipc::Mem::PageStack> *const freeSlotsOwner =
                shm_new(Ipc::Mem::PageStack)(sd->freeSlotsPath(),
                                             i+1, capacity, 0);
            freeSlotsOwners.push_back(freeSlotsOwner);

            // TODO: add method to initialize PageStack with no free pages
            while (true) {
                Ipc::Mem::PageId pageId;
                if (!freeSlotsOwner->object()->pop(pageId))
                    break;
            }
        }
    }
}
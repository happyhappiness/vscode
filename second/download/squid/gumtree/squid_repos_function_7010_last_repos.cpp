void Kids::init()
{
    storage.clear();

    storage.reserve(NumberOfKids());

    char kid_name[32];

    // add Kid records for all workers
    for (int i = 0; i < Config.workers; ++i) {
        snprintf(kid_name, sizeof(kid_name), "(squid-%d)", (int)(storage.size()+1));
        storage.push_back(Kid(kid_name));
    }

    // add Kid records for all disk processes
    for (int i = 0; i < Config.cacheSwap.n_strands; ++i) {
        snprintf(kid_name, sizeof(kid_name), "(squid-disk-%d)", (int)(storage.size()+1));
        storage.push_back(Kid(kid_name));
    }

    // if coordination is needed, add a Kid record for Coordinator
    if (storage.size() > 1) {
        snprintf(kid_name, sizeof(kid_name), "(squid-coord-%d)", (int)(storage.size()+1));
        storage.push_back(Kid(kid_name));
    }

    Must(storage.size() == static_cast<size_t>(NumberOfKids()));
}
void
StoreController::init()
{
    if (Config.memShared && IamWorkerProcess()) {
        memStore = new MemStore;
        memStore->init();
    }

    swapDir->init();

    if (0 == strcasecmp(Config.store_dir_select_algorithm, "round-robin")) {
        storeDirSelectSwapDir = storeDirSelectSwapDirRoundRobin;
        debugs(47, DBG_IMPORTANT, "Using Round Robin store dir selection");
    } else {
        storeDirSelectSwapDir = storeDirSelectSwapDirLeastLoad;
        debugs(47, DBG_IMPORTANT, "Using Least Load store dir selection");
    }
}
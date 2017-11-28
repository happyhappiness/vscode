 * will try to write clean log files if -kparse fails (becasue it
 * calls fatal()).
 */
int StoreController::store_dirs_rebuilding = 1;

StoreController::StoreController() : swapDir (new StoreHashIndex())
        , memStore(NULL)
{}

StoreController::~StoreController()
{
    delete memStore;
}

/*
 * This function pointer is set according to 'store_dir_select_algorithm'
 * in squid.conf.
 */
STDIRSELECT *storeDirSelectSwapDir = storeDirSelectSwapDirLeastLoad;

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
        debugs(47, 1, "Using Round Robin store dir selection");
    } else {

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

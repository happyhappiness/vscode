void
Store::Controller::init()
{
    if (Config.memShared && IamWorkerProcess()) {
        memStore = new MemStore;
        memStore->init();
    }

    swapDir->init();

    if (UsingSmp() && IamWorkerProcess() && Config.onoff.collapsed_forwarding &&
            smpAware()) {
        transients = new Transients;
        transients->init();
    }
}
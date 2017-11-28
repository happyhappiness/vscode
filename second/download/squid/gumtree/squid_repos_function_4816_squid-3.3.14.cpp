void
Rock::SwapDir::init()
{
    debugs(47,2, HERE);

    // XXX: SwapDirs aren't refcounted. We make IORequestor calls, which
    // are refcounted. We up our count once to avoid implicit delete's.
    RefCountReference();

    Must(!map);
    map = new DirMap(path);

    const char *ioModule = needsDiskStrand() ? "IpcIo" : "Blocking";
    if (DiskIOModule *m = DiskIOModule::Find(ioModule)) {
        debugs(47,2, HERE << "Using DiskIO module: " << ioModule);
        io = m->createStrategy();
        io->init();
    } else {
        debugs(47, DBG_CRITICAL, "FATAL: Rock store is missing DiskIO module: " <<
               ioModule);
        fatal("Rock Store missing a required DiskIO module");
    }

    theFile = io->newFile(filePath);
    theFile->configure(fileConfig);
    theFile->open(O_RDWR, 0644, this);

    // Increment early. Otherwise, if one SwapDir finishes rebuild before
    // others start, storeRebuildComplete() will think the rebuild is over!
    // TODO: move store_dirs_rebuilding hack to store modules that need it.
    ++StoreController::store_dirs_rebuilding;
}
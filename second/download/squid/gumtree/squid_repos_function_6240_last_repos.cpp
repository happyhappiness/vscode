void
DiskIOModule::SetupAllModules()
{
#if HAVE_DISKIO_MODULE_AIO
    AIODiskIOModule::GetInstance();
#endif
#if HAVE_DISKIO_MODULE_BLOCKING
    BlockingDiskIOModule::GetInstance();
#endif
#if HAVE_DISKIO_MODULE_DISKDAEMON
    DiskDaemonDiskIOModule::GetInstance();
#endif
#if HAVE_DISKIO_MODULE_DISKTHREADS
    DiskThreadsDiskIOModule::GetInstance();
#endif
#if HAVE_DISKIO_MODULE_IPCIO
    IpcIoDiskIOModule::GetInstance();
#endif
#if HAVE_DISKIO_MODULE_MMAPPED
    MmappedDiskIOModule::GetInstance();
#endif

    for (iterator i = GetModules().begin(); i != GetModules().end(); ++i)
        /* Call the FS to set up capabilities and initialize the FS driver */
        (*i)->init();
}
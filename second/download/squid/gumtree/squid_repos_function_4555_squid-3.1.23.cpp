void Fs::Init()
{

#ifdef HAVE_FS_UFS
    UfsInstance = new StoreFSufs<UFSSwapDir>("Blocking", "ufs");
#endif

#ifdef HAVE_FS_AUFS
    AufsInstance = new StoreFSufs<UFSSwapDir>("DiskThreads", "aufs");;
#endif


#ifdef HAVE_FS_DISKD
    DiskdInstance = new StoreFSufs<UFSSwapDir>("DiskDaemon", "diskd");;
#endif

}
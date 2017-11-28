void Fs::Init()
{

#if HAVE_FS_UFS
    UfsInstance = new Fs::Ufs::StoreFSufs<Fs::Ufs::UFSSwapDir>("Blocking", "ufs");
#endif

#if HAVE_FS_AUFS
    AufsInstance = new Fs::Ufs::StoreFSufs<Fs::Ufs::UFSSwapDir>("DiskThreads", "aufs");;
#endif

#if HAVE_FS_DISKD
    DiskdInstance = new Fs::Ufs::StoreFSufs<Fs::Ufs::UFSSwapDir>("DiskDaemon", "diskd");;
#endif

#if HAVE_FS_ROCK
    RockInstance = new Rock::StoreFileSystem();
#endif

}
void Fs::Clean()
{
#if HAVE_FS_UFS
    delete UfsInstance;
#endif

#if HAVE_FS_AUFS
    delete AufsInstance;
#endif

#if HAVE_FS_DISKD
    delete DiskdInstance;
#endif

#if HAVE_FS_ROCK
    delete RockInstance;
#endif

}
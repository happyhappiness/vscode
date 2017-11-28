void Fs::Clean()
{
#ifdef HAVE_FS_UFS
    delete UfsInstance;
#endif

#ifdef HAVE_FS_AUFS
    delete AufsInstance;
#endif


#ifdef HAVE_FS_DISKD
    delete DiskdInstance;
#endif

}
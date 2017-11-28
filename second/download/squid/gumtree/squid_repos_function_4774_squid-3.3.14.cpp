void
CossSwapDir::init()
{
    /* FIXME: SwapDirs aren't refcounted. We call IORequestor calls, which
     * are refcounted. SO, we up our count once to avoid implicit delete's.
     */
    RefCountReference();
    io->init();
    openLog();
    storeCossDirRebuild(this);
    theFile = io->newFile(stripePath());
    theFile->open(O_RDWR | O_CREAT, 0644, this);

    ++n_coss_dirs;
    /*
     * fs.blksize is normally determined by calling statvfs() etc,
     * but we just set it here.  It is used in accounting the
     * total store size, and is reported in cachemgr 'storedir'
     * page.
     */
    fs.blksize = 1 << blksz_bits;
}
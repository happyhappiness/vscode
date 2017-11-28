void
Rock::Rebuild::start()
{
    // in SMP mode, only the disker is responsible for populating the map
    if (UsingSmp() && !IamDiskProcess()) {
        debugs(47, 2, "Non-disker skips rebuilding of cache_dir #" <<
               sd->index << " from " << sd->filePath);
        mustStop("non-disker");
        return;
    }

    debugs(47, DBG_IMPORTANT, "Loading cache_dir #" << sd->index <<
           " from " << sd->filePath);

    fd = file_open(sd->filePath, O_RDONLY | O_BINARY);
    if (fd < 0)
        failure("cannot open db", errno);

    char hdrBuf[SwapDir::HeaderSize];
    if (read(fd, hdrBuf, sizeof(hdrBuf)) != SwapDir::HeaderSize)
        failure("cannot read db header", errno);

    // slot prefix of SM_PAGE_SIZE should fit both core entry header and ours
    assert(sizeof(DbCellHeader) < SM_PAGE_SIZE);
    buf.init(SM_PAGE_SIZE, SM_PAGE_SIZE);

    dbOffset = SwapDir::HeaderSize;

    parts = new LoadingParts(dbEntryLimit, dbSlotLimit);

    checkpoint();
}
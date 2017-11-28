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

    char buf[SwapDir::HeaderSize];
    if (read(fd, buf, sizeof(buf)) != SwapDir::HeaderSize)
        failure("cannot read db header", errno);

    dbOffset = SwapDir::HeaderSize;
    filen = 0;

    checkpoint();
}
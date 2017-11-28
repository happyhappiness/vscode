void
Rock::Rebuild::doOneEntry()
{
    debugs(47,5, HERE << sd->index << " filen " << filen << " at " <<
           dbOffset << " <= " << dbSize);

    ++counts.scancount;

    if (lseek(fd, dbOffset, SEEK_SET) < 0)
        failure("cannot seek to db entry", errno);

    MemBuf buf;
    buf.init(SM_PAGE_SIZE, SM_PAGE_SIZE);

    if (!storeRebuildLoadEntry(fd, sd->index, buf, counts))
        return;

    // get our header
    DbCellHeader header;
    if (buf.contentSize() < static_cast<mb_size_t>(sizeof(header))) {
        debugs(47, DBG_IMPORTANT, "WARNING: cache_dir[" << sd->index << "]: " <<
               "Ignoring truncated cache entry meta data at " << dbOffset);
        ++counts.invalid;
        return;
    }
    memcpy(&header, buf.content(), sizeof(header));

    if (!header.sane()) {
        debugs(47, DBG_IMPORTANT, "WARNING: cache_dir[" << sd->index << "]: " <<
               "Ignoring malformed cache entry meta data at " << dbOffset);
        ++counts.invalid;
        return;
    }
    buf.consume(sizeof(header)); // optimize to avoid memmove()

    cache_key key[SQUID_MD5_DIGEST_LENGTH];
    StoreEntry loadedE;
    if (!storeRebuildParseEntry(buf, loadedE, key, counts, header.payloadSize)) {
        // skip empty slots
        if (loadedE.swap_filen > 0 || loadedE.swap_file_sz > 0) {
            ++counts.invalid;
            //sd->unlink(filen); leave garbage on disk, it should not hurt
        }
        return;
    }

    assert(loadedE.swap_filen < dbEntryLimit);
    if (!storeRebuildKeepEntry(loadedE, key, counts))
        return;

    ++counts.objcount;
    // loadedE->dump(5);

    sd->addEntry(filen, header, loadedE);
}
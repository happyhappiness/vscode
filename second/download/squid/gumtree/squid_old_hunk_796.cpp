        eventAdd("Rock::Rebuild", Rock::Rebuild::Steps, this, 0.01, 1, true);
}

bool
Rock::Rebuild::doneAll() const
{
    return dbOffset >= dbSize && AsyncJob::doneAll();
}

void
Rock::Rebuild::Steps(void *data)
{
    // use async call to enable job call protection that time events lack
    CallJobHere(47, 5, static_cast<Rebuild*>(data), Rock::Rebuild, steps);
}

void
Rock::Rebuild::steps()
{
    debugs(47,5, HERE << sd->index << " filen " << filen << " at " <<
           dbOffset << " <= " << dbSize);

    // Balance our desire to maximize the number of entries processed at once
    // (and, hence, minimize overheads and total rebuild time) with a
    // requirement to also process Coordinator events, disk I/Os, etc.
    const int maxSpentMsec = 50; // keep small: most RAM I/Os are under 1ms
    const timeval loopStart = current_time;

    int loaded = 0;
    while (loaded < dbEntryLimit && dbOffset < dbSize) {
        doOneEntry();
        dbOffset += dbEntrySize;
        ++filen;
        ++loaded;

        if (counts.scancount % 1000 == 0)
            storeRebuildProgress(sd->index, dbEntryLimit, counts.scancount);

        if (opt_foreground_rebuild)
            continue; // skip "few entries at a time" check below

        getCurrentTime();
        const double elapsedMsec = tvSubMsec(loopStart, current_time);
        if (elapsedMsec > maxSpentMsec || elapsedMsec < 0) {
            debugs(47, 5, HERE << "pausing after " << loaded << " entries in " <<
                   elapsedMsec << "ms; " << (elapsedMsec/loaded) << "ms per entry");
            break;
        }
    }

    checkpoint();
}

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

void
Rock::Rebuild::swanSong()
{
    debugs(47,3, HERE << "cache_dir #" << sd->index << " rebuild level: " <<

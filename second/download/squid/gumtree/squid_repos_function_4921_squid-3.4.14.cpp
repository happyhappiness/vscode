void
Rock::SwapDir::writeCompleted(int errflag, size_t rlen, RefCount< ::WriteRequest> r)
{
    Rock::WriteRequest *request = dynamic_cast<Rock::WriteRequest*>(r.getRaw());
    assert(request);
    assert(request->sio !=  NULL);
    IoState &sio = *request->sio;

    if (errflag == DISK_OK) {
        // close, assuming we only write once; the entry gets the read lock
        map->closeForWriting(sio.swap_filen, true);
        // do not increment sio.offset_ because we do it in sio->write()
    } else {
        // Do not abortWriting here. The entry should keep the write lock
        // instead of losing association with the store and confusing core.
        map->free(sio.swap_filen); // will mark as unusable, just in case
    }

    assert(sio.diskOffset + sio.offset_ <= diskOffsetLimit()); // post-factum

    sio.finishedWriting(errflag);
}
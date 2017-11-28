void
Rock::SwapDir::writeCompleted(int errflag, size_t rlen, RefCount< ::WriteRequest> r)
{
    Rock::WriteRequest *request = dynamic_cast<Rock::WriteRequest*>(r.getRaw());
    assert(request);
    assert(request->sio !=  NULL);
    IoState &sio = *request->sio;

    // quit if somebody called IoState::close() while we were waiting
    if (!sio.stillWaiting()) {
        debugs(79, 3, "ignoring closed entry " << sio.swap_filen);
        noteFreeMapSlice(request->sidNext);
        return;
    }

    // TODO: Fail if disk dropped one of the previous write requests.

    if (errflag == DISK_OK) {
        // do not increment sio.offset_ because we do it in sio->write()

        // finalize the shared slice info after writing slice contents to disk
        Ipc::StoreMap::Slice &slice =
            map->writeableSlice(sio.swap_filen, request->sidCurrent);
        slice.size = request->len - sizeof(DbCellHeader);
        slice.next = request->sidNext;

        if (request->eof) {
            assert(sio.e);
            assert(sio.writeableAnchor_);
            sio.e->swap_file_sz = sio.writeableAnchor_->basics.swap_file_sz =
                                      sio.offset_;

            // close, the entry gets the read lock
            map->closeForWriting(sio.swap_filen, true);
            sio.writeableAnchor_ = NULL;
            sio.finishedWriting(errflag);
        }
    } else {
        noteFreeMapSlice(request->sidNext);

        writeError(*sio.e);
        sio.finishedWriting(errflag);
        // and hope that Core will call disconnect() to close the map entry
    }

    CollapsedForwarding::Broadcast(*sio.e);
}
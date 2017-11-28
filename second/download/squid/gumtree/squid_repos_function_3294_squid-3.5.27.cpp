void
MemStore::write(StoreEntry &e)
{
    assert(e.mem_obj);

    debugs(20, 7, "entry " << e);

    switch (e.mem_obj->memCache.io) {
    case MemObject::ioUndecided:
        if (!shouldCache(e) || !startCaching(e)) {
            e.mem_obj->memCache.io = MemObject::ioDone;
            e.memOutDecision(false);
            return;
        }
        break;

    case MemObject::ioDone:
    case MemObject::ioReading:
        return; // we should not write in all of the above cases

    case MemObject::ioWriting:
        break; // already decided to write and still writing
    }

    try {
        copyToShm(e);
        if (e.store_status == STORE_OK) // done receiving new content
            completeWriting(e);
        else
            CollapsedForwarding::Broadcast(e);
        return;
    } catch (const std::exception &x) { // TODO: should we catch ... as well?
        debugs(20, 2, "mem-caching error writing entry " << e << ": " << x.what());
        // fall through to the error handling code
    }

    disconnect(e);
}
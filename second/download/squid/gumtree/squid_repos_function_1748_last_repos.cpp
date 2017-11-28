bool
mem_hdr::write (StoreIOBuffer const &writeBuffer)
{
    PROF_start(mem_hdr_write);
    debugs(19, 6, "mem_hdr::write: " << this << " " << writeBuffer.range() << " object end " << endOffset());

    if (unionNotEmpty(writeBuffer)) {
        debugs(19, DBG_CRITICAL, "mem_hdr::write: writeBuffer: " << writeBuffer.range());
        debugDump();
        fatal_dump("Attempt to overwrite already in-memory data. Preceding this there should be a mem_hdr::write output that lists the attempted write, and the currently present data. Please get a 'backtrace full' from this error - using the generated core, and file a bug report with the squid developers including the last 10 lines of cache.log and the backtrace.\n");
        PROF_stop(mem_hdr_write);
        return false;
    }

    assert (writeBuffer.offset >= 0);

    mem_node *target;
    int64_t currentOffset = writeBuffer.offset;
    char *currentSource = writeBuffer.data;
    size_t len = writeBuffer.length;

    while (len && (target = nodeToRecieve(currentOffset))) {
        size_t wrote = writeAvailable(target, currentOffset, len, currentSource);
        assert (wrote);
        len -= wrote;
        currentOffset += wrote;
        currentSource += wrote;
    }

    PROF_stop(mem_hdr_write);
    return true;
}
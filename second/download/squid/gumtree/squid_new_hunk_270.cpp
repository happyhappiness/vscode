

bool
mem_hdr::write (StoreIOBuffer const &writeBuffer)
{
    PROF_start(mem_hdr_write);
    debugs(19, 6, "mem_hdr::write: " << this << " " << writeBuffer.range() << " object end " << endOffset());

    if (unionNotEmpty(writeBuffer)) {
        debugs(19,0,"mem_hdr::write: writeBuffer: " << writeBuffer.range());
        debugDump();
        fatal("Attempt to overwrite already in-memory data. Preceeding this there should be a mem_hdr::write output that lists the attempted write, and the currently present data. Please get a 'backtrace full' from this error - using the generated core, and file a bug report with the squid developers including the last 10 lines of cache.log and the backtrace.\n");
        PROF_stop(mem_hdr_write);

void
Log::Format::SquidCustom(const AccessLogEntry::Pointer &al, CustomLog * log)
{
    static MemBuf mb;
    mb.reset();

    // XXX: because we do not yet have a neutral form of transaction slab. use AccessLogEntry
    log->logFormat->assemble(mb, al, log->logfile->sequence_number);

    logfilePrintf(log->logfile, "%s\n", mb.buf);
}
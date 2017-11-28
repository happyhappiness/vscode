void
Rock::Rebuild::failure(const char *msg, int errNo)
{
    debugs(47,5, HERE << sd->index << " filen " << filen << " at " <<
           dbOffset << " <= " << dbSize);

    if (errNo)
        debugs(47, DBG_CRITICAL, "ERROR: Rock cache_dir rebuild failure: " << xstrerr(errNo));
    debugs(47, DBG_CRITICAL, "Do you need to run 'squid -z' to initialize storage?");

    assert(sd);
    fatalf("Rock cache_dir[%d] rebuild of %s failed: %s.",
           sd->index, sd->filePath, msg);
}
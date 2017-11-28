void
Rock::SwapDir::createError(const char *const msg)
{
    debugs(47, DBG_CRITICAL, "ERROR: Failed to initialize Rock Store db in " <<
           filePath << "; " << msg << " error: " << xstrerror());
    fatal("Rock Store db creation error");
}
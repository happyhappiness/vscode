void
Debug::xassert(const char *msg, const char *file, int line)
{

    if (CurrentDebug) {
        *CurrentDebug << "assertion failed: " << file << ":" << line <<
        ": \"" << msg << "\"";
    }
    abort();
}
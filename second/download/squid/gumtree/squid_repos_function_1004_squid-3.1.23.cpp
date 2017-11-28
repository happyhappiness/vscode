void
xassert(const char *msg, const char *file, int line)
{
    debugs(0, 0, "assertion failed: " << file << ":" << line << ": \"" << msg << "\"");

    if (!shutting_down)
        abort();
}
void
BlockingIOStrategy::unlinkFile(char const *path)
{
#if USE_UNLINKD
    unlinkdUnlink(path);
#else
    ::unlink(path);
#endif
}
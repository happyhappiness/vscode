void Adaptation::Icap::VirginBodyAct::progress(size_t size)
{
    Must(active());
#if SIZEOF_SIZE_T > 4
    /* always true for smaller size_t's */
    Must(static_cast<int64_t>(size) >= 0);
#endif
    theStart += static_cast<int64_t>(size);
}
void
String::clean()
{
    PROF_start(StringClean);
    assert(this);

    /* TODO if mempools has already closed this will FAIL!! */
    if (defined())
        memFreeString(size_, buf_);

    len_ = 0;

    size_ = 0;

    buf_ = NULL;
    PROF_stop(StringClean);
}
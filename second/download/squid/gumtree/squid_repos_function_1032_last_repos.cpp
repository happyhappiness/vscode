void
String::append( char const *str, int len)
{
    assert(str && len >= 0);

    PROF_start(StringAppend);
    if (len_ + len < size_) {
        strncat(buf_, str, len);
        len_ += len;
    } else {
        // Create a temporary string and absorb it later.
        String snew;
        assert(canGrowBy(len)); // otherwise snew.len_ may overflow below
        snew.len_ = len_ + len;
        snew.allocBuffer(snew.len_ + 1);

        if (len_)
            memcpy(snew.buf_, rawBuf(), len_);

        if (len)
            memcpy(snew.buf_ + len_, str, len);

        snew.buf_[snew.len_] = '\0';

        absorb(snew);
    }
    PROF_stop(StringAppend);
}
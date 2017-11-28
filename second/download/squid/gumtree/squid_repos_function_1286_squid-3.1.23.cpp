void
String::append(const char *str, int len)
{
    assert(this);
    assert(str && len >= 0);

    PROF_start(StringAppend);
    if (len_ + len < size_) {
        strncat(buf_, str, len);
        len_ += len;
    } else {
        // Create a temporary string and absorb it later.
        String snew;
        assert(len_ + len < 65536); // otherwise snew.len_ overflows below
        snew.len_ = len_ + len;
        snew.allocBuffer(snew.len_ + 1);

        if (len_)
            xmemcpy(snew.buf_, rawBuf(), len_);

        if (len)
            xmemcpy(snew.buf_ + len_, str, len);

        snew.buf_[snew.len_] = '\0';

        absorb(snew);
    }
    PROF_stop(StringAppend);
}
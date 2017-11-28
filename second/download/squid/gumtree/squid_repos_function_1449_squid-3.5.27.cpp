bool
SBuf::operator ==(const SBuf & S) const
{
    debugs(24, 8, id << " == " << S.id);
    if (length() != S.length()) {
        debugs(24, 8, "no, different lengths");
        ++stats.compareFast;
        return false; //shortcut: must be equal length
    }
    if (store_ == S.store_ && off_ == S.off_) {
        debugs(24, 8, "yes, same length and backing store");
        ++stats.compareFast;
        return true;  //shortcut: same store, offset and length
    }
    ++stats.compareSlow;
    const bool rv = (0 == memcmp(buf(), S.buf(), length()));
    debugs(24, 8, "returning " << rv);
    return rv;
}
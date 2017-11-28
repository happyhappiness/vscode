SBuf&
SBuf::assign(const SBuf &S)
{
    debugs(24, 7, "assigning " << id << " from " <<  S.id);
    if (&S == this) //assignment to self. Noop.
        return *this;
    ++stats.assignFast;
    store_ = S.store_;
    off_ = S.off_;
    len_ = S.len_;
    return *this;
}
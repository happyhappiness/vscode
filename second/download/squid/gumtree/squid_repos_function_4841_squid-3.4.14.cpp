void
CossMemBuf::maybeWrite(CossSwapDir * SD)
{
    describe(3, __LINE__);

    if (!flags.full)
        debugs(79, 3, "membuf " << this << " not full");
    else if (flags.writing)
        debugs(79, 3, "membuf " << this << " writing");
    else if (lockcount)
        debugs(79, 3, "membuf " << this << " lockcount=" << lockcount);
    else
        write(SD);
}
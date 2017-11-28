int64_t
HttpHdrRangeIter::debt() const
{
    debugs(64, 3, "HttpHdrRangeIter::debt: debt is " << debt_size);
    return debt_size;
}
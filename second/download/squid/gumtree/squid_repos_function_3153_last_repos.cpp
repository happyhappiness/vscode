void HttpHdrRangeIter::debt(int64_t newDebt)
{
    debugs(64, 3, "HttpHdrRangeIter::debt: was " << debt_size << " now " << newDebt);
    debt_size = newDebt;
}
static int
DBG_INDEX(int sz)
{
    if (sz >= DBG_MAXSIZE)
        return DBG_MAXINDEX;

    if (sz <= DBG_SPLIT)
        return (sz + DBG_GRAIN_SM - 1) / DBG_GRAIN_SM;

    return (sz + DBG_GRAIN - 1) / DBG_GRAIN + DBG_OFFSET;
}
static int
XMS_DBG_INDEX(int sz)
{
    if (sz >= XMS_DBG_MAXSIZE)
        return XMS_DBG_MAXINDEX;

    if (sz <= XMS_DBG_SPLIT)
        return (sz + XMS_DBG_GRAIN_SM - 1) / XMS_DBG_GRAIN_SM;

    return (sz + XMS_DBG_GRAIN - 1) / XMS_DBG_GRAIN + XMS_DBG_OFFSET;
}
void
httpHdrCcStatDumper(StoreEntry * sentry, int, double val, double, int count)
{
    extern const HttpHeaderStat *dump_stat; /* argh! */
    const int id = static_cast<int>(val);
    const bool valid_id = id >= 0 && id < static_cast<int>(HttpHdrCcType::CC_ENUM_END);
    const char *name = valid_id ? CcAttrs[id].name : "INVALID";

    if (count || valid_id)
        storeAppendPrintf(sentry, "%2d\t %-20s\t %5d\t %6.2f\n",
                          id, name, count, xdiv(count, dump_stat->ccParsedCount));
}
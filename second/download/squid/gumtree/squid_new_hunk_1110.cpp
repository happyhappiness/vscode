HttpHeaderEntry::clone() const
{
    return new HttpHeaderEntry(id, name.termedBuf(), value.termedBuf());
}

void
HttpHeaderEntry::packInto(Packable * p) const
{
    assert(p);
    p->append(name.rawBuf(), name.size());
    p->append(": ", 2);
    p->append(value.rawBuf(), value.size());
    p->append("\r\n", 2);
}

int
HttpHeaderEntry::getInt() const
{
    int val = -1;
    int ok = httpHeaderParseInt(value.termedBuf(), &val);
    httpHeaderNoteParsedEntry(id, value, ok == 0);
    /* XXX: Should we check ok - ie
     * return ok ? -1 : value;
     */
    return val;
}

int64_t
HttpHeaderEntry::getInt64() const
{
    int64_t val = -1;
    const bool ok = httpHeaderParseOffset(value.termedBuf(), &val);
    httpHeaderNoteParsedEntry(id, value, !ok);
    return val; // remains -1 if !ok (XXX: bad method API)
}

static void
httpHeaderNoteParsedEntry(Http::HdrType id, String const &context, bool error)
{
    if (id != Http::HdrType::BAD_HDR)
        ++ headerStatsTable[id].parsCount;

    if (error) {
        if (id != Http::HdrType::BAD_HDR)
            ++ headerStatsTable[id].errCount;
        debugs(55, 2, "cannot parse hdr field: '" << Http::HeaderLookupTable.lookup(id).name << ": " << context << "'");
    }
}

/*
 * Reports
 */

/* tmp variable used to pass stat info to dumpers */
extern const HttpHeaderStat *dump_stat;     /* argh! */
const HttpHeaderStat *dump_stat = NULL;

void
httpHeaderFieldStatDumper(StoreEntry * sentry, int, double val, double, int count)
{
    const int id = static_cast<int>(val);
    const bool valid_id = Http::any_valid_header(static_cast<Http::HdrType>(id));
    const char *name = valid_id ? Http::HeaderLookupTable.lookup(static_cast<Http::HdrType>(id)).name : "INVALID";
    int visible = count > 0;
    /* for entries with zero count, list only those that belong to current type of message */

    if (!visible && valid_id && dump_stat->owner_mask)
        visible = CBIT_TEST(*dump_stat->owner_mask, id);

    if (visible)
        storeAppendPrintf(sentry, "%2d\t %-20s\t %5d\t %6.2f\n",
                          id, name, count, xdiv(count, dump_stat->busyDestroyedCount));
}

static void
httpHeaderFldsPerHdrDumper(StoreEntry * sentry, int idx, double val, double, int count)
{
    if (count)
        storeAppendPrintf(sentry, "%2d\t %5d\t %5d\t %6.2f\n",
                          idx, (int) val, count,
                          xpercent(count, dump_stat->destroyedCount));
}

static void
httpHeaderStatDump(const HttpHeaderStat * hs, StoreEntry * e)
{
    assert(hs);
    assert(e);

    dump_stat = hs;
    storeAppendPrintf(e, "\nHeader Stats: %s\n", hs->label);
    storeAppendPrintf(e, "\nField type distribution\n");
    storeAppendPrintf(e, "%2s\t %-20s\t %5s\t %6s\n",
                      "id", "name", "count", "#/header");

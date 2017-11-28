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
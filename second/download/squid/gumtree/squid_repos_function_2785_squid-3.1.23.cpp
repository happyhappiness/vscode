static void
httpHeaderNoteParsedEntry(http_hdr_type id, String const &context, int error)
{
    Headers[id].stat.parsCount++;

    if (error) {
        Headers[id].stat.errCount++;
        debugs(55, 2, "cannot parse hdr field: '" << Headers[id].name << ": " << context << "'");
    }
}
bool
Http::ContentLengthInterpreter::checkList(const String &list)
{
    Must(!sawBad);

    if (!Config.onoff.relaxed_header_parser) {
        debugs(55, debugLevel, "WARNING: List-like" << Raw("Content-Length", list.rawBuf(), list.size()));
        sawBad = true;
        return false;
    }

    needsSanitizing = true; // remove extra commas (at least)

    const char *pos = nullptr;
    const char *item = nullptr;;
    int ilen = -1;
    while (strListGetItem(&list, ',', &item, &ilen, &pos)) {
        if (!checkValue(item, ilen) && sawBad)
            break;
        // keep going after a duplicate value to find conflicting ones
    }
    return false; // no need to keep this list field; it will be sanitized away
}
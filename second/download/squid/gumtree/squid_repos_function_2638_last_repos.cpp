bool strHdrAcptLangGetItem(const String &hdr, char *lang, int langLen, size_t &pos)
{
    while (pos < hdr.size()) {

        /* skip any initial whitespace. */
        while (pos < hdr.size() && xisspace(hdr[pos]))
            ++pos;

        /*
         * Header value format:
         *  - sequence of whitespace delimited tags
         *  - each tag may suffix with ';'.* which we can ignore.
         *  - IFF a tag contains only two characters we can wildcard ANY translations matching: <it> '-'? .*
         *    with preference given to an exact match.
         */
        bool invalid_byte = false;
        char *dt = lang;
        while (pos < hdr.size() && hdr[pos] != ';' && hdr[pos] != ',' && !xisspace(hdr[pos]) && dt < (lang + (langLen -1)) ) {
            if (!invalid_byte) {
#if USE_HTTP_VIOLATIONS
                // if accepting violations we may as well accept some broken browsers
                //  which may send us the right code, wrong ISO formatting.
                if (hdr[pos] == '_')
                    *dt = '-';
                else
#endif
                    *dt = xtolower(hdr[pos]);
                // valid codes only contain A-Z, hyphen (-) and *
                if (*dt != '-' && *dt != '*' && (*dt < 'a' || *dt > 'z') )
                    invalid_byte = true;
                else
                    ++dt; // move to next destination byte.
            }
            ++pos;
        }
        *dt = '\0'; // nul-terminated the filename content string before system use.

        // if we terminated the tag on garbage or ';' we need to skip to the next ',' or end of header.
        while (pos < hdr.size() && hdr[pos] != ',')
            ++pos;

        if (pos < hdr.size() && hdr[pos] == ',')
            ++pos;

        debugs(4, 9, "STATE: lang=" << lang << ", pos=" << pos << ", buf='" << ((pos < hdr.size()) ? hdr.substr(pos,hdr.size()) : "") << "'");

        /* if we found anything we might use, try it. */
        if (*lang != '\0' && !invalid_byte)
            return true;
    }
    return false;
}
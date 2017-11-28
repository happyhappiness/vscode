int
httpHeaderParseQuotedString(const char *start, const int len, String *val)
{
    const char *end, *pos;
    val->clean();
    if (*start != '"') {
        debugs(66, 2, HERE << "failed to parse a quoted-string header field near '" << start << "'");
        return 0;
    }
    pos = start + 1;

    while (*pos != '"' && len > (pos-start)) {

        if (*pos =='\r') {
            ++pos;
            if ((pos-start) > len || *pos != '\n') {
                debugs(66, 2, HERE << "failed to parse a quoted-string header field with '\\r' octet " << (start-pos)
                       << " bytes into '" << start << "'");
                val->clean();
                return 0;
            }
        }

        if (*pos == '\n') {
            ++pos;
            if ( (pos-start) > len || (*pos != ' ' && *pos != '\t')) {
                debugs(66, 2, HERE << "failed to parse multiline quoted-string header field '" << start << "'");
                val->clean();
                return 0;
            }
            // TODO: replace the entire LWS with a space
            val->append(" ");
            ++pos;
            debugs(66, 2, HERE << "len < pos-start => " << len << " < " << (pos-start));
            continue;
        }

        bool quoted = (*pos == '\\');
        if (quoted) {
            ++pos;
            if (!*pos || (pos-start) > len) {
                debugs(66, 2, HERE << "failed to parse a quoted-string header field near '" << start << "'");
                val->clean();
                return 0;
            }
        }
        end = pos;
        while (end < (start+len) && *end != '\\' && *end != '\"' && (unsigned char)*end > 0x1F && *end != 0x7F)
            ++end;
        if (((unsigned char)*end <= 0x1F && *end != '\r' && *end != '\n') || *end == 0x7F) {
            debugs(66, 2, HERE << "failed to parse a quoted-string header field with CTL octet " << (start-pos)
                   << " bytes into '" << start << "'");
            val->clean();
            return 0;
        }
        val->append(pos, end-pos);
        pos = end;
    }

    if (*pos != '\"') {
        debugs(66, 2, HERE << "failed to parse a quoted-string header field which did not end with \" ");
        val->clean();
        return 0;
    }
    /* Make sure it's defined even if empty "" */
    if (!val->defined())
        val->limitInit("", 0);
    return 1;
}
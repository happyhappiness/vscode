int
httpHeaderParseQuotedString (const char *start, String *val)
{
    const char *end, *pos;
    val->clean();
    if (*start != '"') {
        debugs(66, 2, "failed to parse a quoted-string header field near '" << start << "'");
        return 0;
    }
    pos = start + 1;

    while (*pos != '"') {
        bool quoted = (*pos == '\\');
        if (quoted)
            pos++;
        if (!*pos) {
            debugs(66, 2, "failed to parse a quoted-string header field near '" << start << "'");
            val->clean();
            return 0;
        }
        end = pos + strcspn(pos + quoted, "\"\\") + quoted;
        val->append(pos, end-pos);
        pos = end;
    }
    /* Make sure it's defined even if empty "" */
    if (!val->defined())
        val->limitInit("", 0);
    return 1;
}
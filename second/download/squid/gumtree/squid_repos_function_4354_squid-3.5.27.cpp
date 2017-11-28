void
Helper::Reply::parseResponseKeys()
{
    // parse a "key=value" pair off the 'other()' buffer.
    while (other().hasContent()) {
        char *p = modifiableOther().content();
        while (*p && isKeyNameChar(*p)) ++p;
        if (*p != '=')
            return; // done. Not a key.

        // whitespace between key and value is prohibited.
        // workaround strwordtok() which skips whitespace prefix.
        if (xisspace(*(p+1)))
            return; // done. Not a key.

        *p = '\0';
        ++p;

        const char *key = other().content();

        // the value may be a quoted string or a token
        const bool urlDecode = (*p != '"'); // check before moving p.
        char *v = strwordtok(NULL, &p);
        if (v != NULL && urlDecode && (p-v) > 2) // 1-octet %-escaped requires 3 bytes
            rfc1738_unescape(v);

        notes.add(key, v ? v : ""); // value can be empty, but must not be NULL

        modifiableOther().consume(p - other().content());
        modifiableOther().consumeWhitespacePrefix();
    }
}
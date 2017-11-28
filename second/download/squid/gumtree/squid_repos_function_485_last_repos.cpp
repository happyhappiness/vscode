String HttpReply::removeStaleWarningValues(const String &value)
{
    String newValue;
    const char *item = 0;
    int len = 0;
    const char *pos = 0;
    while (strListGetItem(&value, ',', &item, &len, &pos)) {
        bool keep = true;
        // Does warning-value have warn-date (which contains quoted date)?
        // We scan backwards, looking for two quoted strings.
        // warning-value = warn-code SP warn-agent SP warn-text [SP warn-date]
        const char *p = item + len - 1;

        while (p >= item && xisspace(*p)) --p; // skip whitespace

        // warning-value MUST end with quote
        if (p >= item && *p == '"') {
            const char *const warnDateEnd = p;
            --p;
            while (p >= item && *p != '"') --p; // find the next quote

            const char *warnDateBeg = p + 1;
            --p;
            while (p >= item && xisspace(*p)) --p; // skip whitespace

            if (p >= item && *p == '"' && warnDateBeg - p > 2) {
                // found warn-text
                String warnDate;
                warnDate.append(warnDateBeg, warnDateEnd - warnDateBeg);
                const time_t time = parse_rfc1123(warnDate.termedBuf());
                keep = (time > 0 && time == date); // keep valid and matching date
            }
        }

        if (keep) {
            if (newValue.size())
                newValue.append(", ");
            newValue.append(item, len);
        }
    }

    return newValue;
}
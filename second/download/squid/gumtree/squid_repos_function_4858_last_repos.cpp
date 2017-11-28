bool
Http::ContentLengthInterpreter::checkValue(const char *rawValue, const int valueSize)
{
    Must(!sawBad);

    int64_t latestValue = -1;
    char *suffix = nullptr;
    // TODO: Handle malformed values with leading signs (e.g., "-0" or "+1").
    if (!httpHeaderParseOffset(rawValue, &latestValue, &suffix)) {
        debugs(55, DBG_IMPORTANT, "WARNING: Malformed" << Raw("Content-Length", rawValue, valueSize));
        sawBad = true;
        return false;
    }

    if (latestValue < 0) {
        debugs(55, debugLevel, "WARNING: Negative" << Raw("Content-Length", rawValue, valueSize));
        sawBad = true;
        return false;
    }

    // check for garbage after the number
    if (!goodSuffix(suffix, rawValue + valueSize)) {
        debugs(55, debugLevel, "WARNING: Trailing garbage in" << Raw("Content-Length", rawValue, valueSize));
        sawBad = true;
        return false;
    }

    if (sawGood) {
        /* we have found at least two, possibly identical values */

        needsSanitizing = true; // replace identical values with a single value

        const bool conflicting = value != latestValue;
        if (conflicting)
            headerWideProblem = "Conflicting"; // overwrite any lesser problem
        else if (!headerWideProblem) // preserve a possibly worse problem
            headerWideProblem = "Duplicate";

        // with relaxed_header_parser, identical values are permitted
        sawBad = !Config.onoff.relaxed_header_parser || conflicting;
        return false; // conflicting or duplicate
    }

    sawGood = true;
    value = latestValue;
    return true;
}
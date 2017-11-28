bool
ACLRegexData::match(char const *word)
{
    if (!word)
        return 0;

    debugs(28, 3, "checking '" << word << "'");

    // walk the list of patterns to see if one matches
    for (auto &i : data) {
        if (i.match(word)) {
            debugs(28, 2, '\'' << i.c_str() << "' found in '" << word << '\'');
            // TODO: old code also popped the pattern to second place of the list
            // in order to reduce patterns search times.
            return 1;
        }
    }

    return 0;
}
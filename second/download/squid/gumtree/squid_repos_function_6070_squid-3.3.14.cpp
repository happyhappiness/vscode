void
ESIVariableUserAgent::eval (ESIVarState &state, char const *subref, char const *found_default) const
{
    char const *s = NULL;
    state.useragentUsed();

    if (state.header().has(HDR_USER_AGENT)) {
        if (!subref)
            s = state.header().getStr (HDR_USER_AGENT);
        else {
            if (!strcmp (subref, "os")) {
                s = esiUserOs[UserOs];
            } else if (!strcmp (subref, "browser")) {
                s = esiBrowsers[browser];
            } else if (!strcmp (subref, "version")) {
                s = browserVersion();
            } else
                s = "";
        }
    } else
        s = found_default;

    ESISegment::ListAppend (state.getOutput(), s, strlen (s));
}
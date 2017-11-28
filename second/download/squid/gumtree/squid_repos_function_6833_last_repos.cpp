void
ESIVariableCookie::eval (ESIVarState &state, char const *subref, char const *found_default) const
{
    const char *s = NULL;
    state.cookieUsed();

    if (state.header().has(Http::HdrType::COOKIE)) {
        if (!subref)
            s = state.header().getStr (Http::HdrType::COOKIE);
        else {
            String S = state.header().getListMember (Http::HdrType::COOKIE, subref, ';');

            if (S.size())
                ESISegment::ListAppend (state.getOutput(), S.rawBuf(), S.size());
            else if (found_default)
                ESISegment::ListAppend (state.getOutput(), found_default, strlen (found_default));
        }
    } else
        s = found_default;

    if (s)
        ESISegment::ListAppend (state.getOutput(), s, strlen (s));
}
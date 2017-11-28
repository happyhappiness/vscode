void
ESIVariableReferer::eval (ESIVarState &state, char const *subref, char const *found_default) const
{
    const char *s = NULL;
    state.refererUsed();

    if (!subref && state.header().has(HDR_REFERER))
        s = state.header().getStr (HDR_REFERER);
    else
        s = found_default;

    ESISegment::ListAppend (state.getOutput(), s, strlen (s));
}
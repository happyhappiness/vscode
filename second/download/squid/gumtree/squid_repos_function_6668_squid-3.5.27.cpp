void
ESIVariableHost::eval (ESIVarState &state, char const *subref, char const *found_default) const
{
    const char *s = NULL;
    state.hostUsed();

    if (!subref && state.header().has(HDR_HOST)) {
        s = state.header().getStr (HDR_HOST);
    } else
        s = found_default;

    ESISegment::ListAppend (state.getOutput(), s, strlen (s));
}
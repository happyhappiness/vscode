void
ESIVariableReferer::eval (ESIVarState &state, char const *subref, char const *found_default) const
{
    const char *s = NULL;
    state.refererUsed();

    if (!subref && state.header().has(Http::HdrType::REFERER))
        s = state.header().getStr (Http::HdrType::REFERER);
    else
        s = found_default;

    ESISegment::ListAppend (state.getOutput(), s, strlen (s));
}
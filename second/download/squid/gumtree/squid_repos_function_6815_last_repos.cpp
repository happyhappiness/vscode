void
ESIVarState::Variable::eval (ESIVarState &state, char const *subref, char const *found_default) const
{
    /* No-op. We swallow it */

    if (found_default)
        ESISegment::ListAppend (state.getOutput(), found_default, strlen (found_default));
}
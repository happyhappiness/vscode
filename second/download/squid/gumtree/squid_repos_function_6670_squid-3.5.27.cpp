void
ESIVariableQuery::eval (ESIVarState &state, char const *subref, char const *found_default) const
{
    char const *s = NULL;

    if (!subref)
        s = queryString();
    else {
        unsigned int i = 0;

        while (i < queryElements() && !s) {
            if (!strcmp (subref, queryVector()[i].var))
                s = queryVector()[i].val;

            ++i;
        }

        if (!s)
            s = found_default;
    }

    ESISegment::ListAppend (state.getOutput(), s, strlen (s));
}
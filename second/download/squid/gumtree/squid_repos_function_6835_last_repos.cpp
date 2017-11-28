void
ESIVariableLanguage::eval (ESIVarState &state, char const *subref, char const *found_default) const
{
    char const *s = NULL;
    state.languageUsed();

    if (state.header().has(Http::HdrType::ACCEPT_LANGUAGE)) {
        if (!subref) {
            String S (state.header().getList (Http::HdrType::ACCEPT_LANGUAGE));
            ESISegment::ListAppend (state.getOutput(), S.rawBuf(), S.size());
        } else {
            if (state.header().hasListMember (Http::HdrType::ACCEPT_LANGUAGE, subref, ',')) {
                s = "true";
            } else {
                s = "false";
            }

            ESISegment::ListAppend (state.getOutput(), s, strlen (s));
        }
    } else {
        s = found_default;
        ESISegment::ListAppend (state.getOutput(), s, strlen (s));
    }
}
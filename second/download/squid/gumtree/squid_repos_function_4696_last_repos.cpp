bool
IsMember(const SBufList & sl, const SBuf &S, const SBufCaseSensitive case_sensitive)
{
    return std::find_if(sl.begin(), sl.end(), SBufEqual(S,case_sensitive)) != sl.end();
}
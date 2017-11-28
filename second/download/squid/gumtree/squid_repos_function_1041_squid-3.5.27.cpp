static void
ReplaceSubstr(char*& str, int& len, unsigned substrIdx, unsigned substrLen, const char* newSubstr)
{
    assert(str != NULL);
    assert(newSubstr != NULL);

    unsigned newSubstrLen = strlen(newSubstr);
    if (newSubstrLen > substrLen)
        str = (char*)realloc(str, len - substrLen + newSubstrLen + 1);

    // move tail part including zero
    memmove(str + substrIdx + newSubstrLen, str + substrIdx + substrLen, len - substrIdx - substrLen + 1);
    // copy new substring in place
    memcpy(str + substrIdx, newSubstr, newSubstrLen);

    len = strlen(str);
}
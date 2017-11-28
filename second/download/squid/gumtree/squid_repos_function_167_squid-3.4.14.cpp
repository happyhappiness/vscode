static int
StringSplit(char *In_Str, char chr, char *Out_Str, size_t Out_Sz)
{
    if ((In_Str == NULL) || (Out_Str == NULL))
        return (-1);

    size_t In_Len = strlen(In_Str) + 1;

    // find the char delimiter position...
    char *p = In_Str;
    while (*p != chr && *p != '\0' && (In_Str+In_Len) > p) {
        ++p;
    }

    size_t i = (p-In_Str);

    // token to big for the output buffer
    if (i >= Out_Sz)
        return (-2);

    // wipe the unused Out_Obj area
    memset(Out_Str+i, 0, Out_Sz-i);
    // copy token from In_Str to Out_Str
    memcpy(Out_Str, In_Str, i);

    // omit the delimiter
    if (*p == chr) {
        ++p;
        ++i;
    } else {
        // chr not found (or \0 found first). Wipe whole input buffer.
        memset(In_Str, 0, In_Len);
//        return (-3);
// Returning <0 breaks current ConvertIP() code for last object
        return (i);
    }

    // move the unused In_Str forward
    memmove(In_Str, p, In_Len-i);
    // wipe the end of In_Str
    memset(In_Str+In_Len-i, 0, i);
    return (i-1);
}
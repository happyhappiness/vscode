static int
BinarySplit(void *In_Obj, size_t In_Sz, char chr, void *Out_Obj, size_t Out_Sz)
{
    // check tolerances
    if ((In_Obj == NULL) || (Out_Obj == NULL))
        return (-1);

    char *in = static_cast<char*>(In_Obj);
    char *out = static_cast<char*>(Out_Obj);

    // find the char delimiter position...
    char *p = static_cast<char*>(In_Obj);
    while (*p != chr && (in+In_Sz) > p) {
        ++p;
    }

    size_t i = (p-in);

    // token to big for the output buffer
    if (i > Out_Sz)
        return (-2);

    // wipe the unused Out_Obj area
    memset(out+i, 0, Out_Sz-i);
    // copy token from In_Obj to Out_Obj
    memcpy(Out_Obj, In_Obj, i);

    // omit the delimiter
    if (*p == chr) {
        ++p;
        ++i;
    } else {
        // chr not found
        memset(In_Obj, 0, In_Sz);
//        return (-3);
// Returning <0 breaks current code for last object
        return (i);
    }

    // move the unused In_Obj forward
    memmove(In_Obj, p, In_Sz-i);
    // wipe the end of In_Obj
    memset(in+In_Sz-i, 0, i);
    return (i-1);
}
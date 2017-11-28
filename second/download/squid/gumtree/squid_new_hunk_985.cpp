
    storeAppendPrintf(entry, "\n");
}

inline void
free_YesNoNone(YesNoNone *)
{}

static void
parse_YesNoNone(YesNoNone *option)
{
    int value = 0;
    parse_onoff(&value);

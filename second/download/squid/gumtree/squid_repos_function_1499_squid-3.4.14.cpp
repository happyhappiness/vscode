static void
ConfigureCurrentKid(const char *processName)
{
    // kids are marked with parenthesis around their process names
    if (processName && processName[0] == '(') {
        if (const char *idStart = strrchr(processName, '-')) {
            KidIdentifier = atoi(idStart + 1);
            const size_t nameLen = idStart - (processName + 1);
            assert(nameLen < sizeof(TheKidName));
            xstrncpy(TheKidName, processName + 1, nameLen + 1);
            if (!strcmp(TheKidName, "squid-coord"))
                TheProcessKind = pkCoordinator;
            else if (!strcmp(TheKidName, "squid"))
                TheProcessKind = pkWorker;
            else if (!strcmp(TheKidName, "squid-disk"))
                TheProcessKind = pkDisker;
            else
                TheProcessKind = pkOther; // including coordinator
        }
    } else {
        xstrncpy(TheKidName, APP_SHORTNAME, sizeof(TheKidName));
        KidIdentifier = 0;
    }
}
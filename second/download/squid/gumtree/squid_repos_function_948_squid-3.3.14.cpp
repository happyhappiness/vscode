int
GetPercentage(void)
{
    int p;
    char *token = strtok(NULL, w_space);

    if (!token) {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: A percentage value is missing.");
        self_destruct();
    }

    //if there is a % in the end of the digits, we remove it and go on.
    char* end = &token[strlen(token)-1];
    if (*end == '%') {
        *end = '\0';
    }

    p = xatoi(token);

    if (p < 0 || p > 100) {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: The value '" << token << "' is out of range. A percentage should be within [0, 100].");
        self_destruct();
    }

    return p;
}
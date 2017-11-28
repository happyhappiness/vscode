void
ACLRandom::parse()
{
    char *t;
    char bufa[256], bufb[256];

    t = strtokFile();
    if (!t) {
        debugs(28, DBG_PARSE_NOTE(DBG_IMPORTANT), "ACL random missing pattern");
        return;
    }

    debugs(28, 5, "aclParseRandomData: " << t);

    // seed random generator ...
    srand(time(NULL));

    if (sscanf(t, "%[0-9]:%[0-9]", bufa, bufb) == 2) {
        int a = xatoi(bufa);
        int b = xatoi(bufb);
        if (a <= 0 || b <= 0) {
            debugs(28, DBG_CRITICAL, "ERROR: ACL random with bad pattern: '" << t << "'");
            return;
        } else
            data = a / (double)(a+b);
    } else if (sscanf(t, "%[0-9]/%[0-9]", bufa, bufb) == 2) {
        int a = xatoi(bufa);
        int b = xatoi(bufb);
        if (a <= 0 || b <= 0) {
            debugs(28, DBG_CRITICAL, "ERROR: ACL random with bad pattern: '" << t << "'");
            return;
        } else
            data = (double) a / (double) b;
    } else if (sscanf(t, "0.%[0-9]", bufa) == 1) {
        data = atof(t);
    } else {
        debugs(28, DBG_CRITICAL, "ERROR: ACL random with bad pattern: '" << t << "'");
        return;
    }

    // save the exact input pattern. so we can display it later.
    memcpy(pattern, t, min(sizeof(pattern)-1,strlen(t)));
}
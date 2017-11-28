    if (flags.useragent)
        strcat (tempstr, "User-Agent ");

    if (!tempstr[0])
        return;

    String strVary (rep->header.getList (Http::HdrType::VARY));

    if (!strVary.size() || strVary[0] != '*') {
        rep->header.putStr (Http::HdrType::VARY, tempstr);
    }
}


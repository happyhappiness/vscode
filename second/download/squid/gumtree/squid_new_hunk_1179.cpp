
    HttpHeaderPos pos = HttpHeaderInitPos;
    bool hasEPRT = false;
    bool hasEPSV = false;
    int prependSpaces = 1;

    featReply->header.putStr(Http::HdrType::FTP_PRE, "\"211-Features:\"");
    const int scode = serverReplyHeader.getInt(Http::HdrType::FTP_STATUS);
    if (scode == 211) {
        while (const HttpHeaderEntry *e = serverReplyHeader.getEntry(&pos)) {
            if (e->id == Http::HdrType::FTP_PRE) {
                // assume RFC 2389 FEAT response format, quoted by Squid:
                // <"> SP NAME [SP PARAMS] <">
                // but accommodate MS servers sending four SPs before NAME

                // command name ends with (SP parameter) or quote
                static const CharacterSet AfterFeatNameChars("AfterFeatName", " \"");

void
Ftp::Server::handleFeatReply(const HttpReply *reply, StoreIOBuffer)
{
    if (getCurrentContext()->http->request->errType != ERR_NONE) {
        writeCustomReply(502, "Server does not support FEAT", reply);
        return;
    }

    Must(reply);
    HttpReply::Pointer featReply = Ftp::HttpReplyWrapper(211, "End", Http::scNoContent, 0);
    HttpHeader const &serverReplyHeader = reply->header;

    HttpHeaderPos pos = HttpHeaderInitPos;
    bool hasEPRT = false;
    bool hasEPSV = false;
    int prependSpaces = 1;

    featReply->header.putStr(HDR_FTP_PRE, "\"211-Features:\"");
    const int scode = serverReplyHeader.getInt(HDR_FTP_STATUS);
    if (scode == 211) {
        while (const HttpHeaderEntry *e = serverReplyHeader.getEntry(&pos)) {
            if (e->id == HDR_FTP_PRE) {
                // assume RFC 2389 FEAT response format, quoted by Squid:
                // <"> SP NAME [SP PARAMS] <">
                // but accommodate MS servers sending four SPs before NAME

                // command name ends with (SP parameter) or quote
                static const CharacterSet AfterFeatNameChars("AfterFeatName", " \"");
                static const CharacterSet FeatNameChars = AfterFeatNameChars.complement("FeatName");

                Parser::Tokenizer tok(SBuf(e->value.termedBuf()));
                if (!tok.skip('"') || !tok.skip(' '))
                    continue;

                // optional spaces; remember their number to accomodate MS servers
                prependSpaces = 1 + tok.skipAll(CharacterSet::SP);

                SBuf cmd;
                if (!tok.prefix(cmd, FeatNameChars))
                    continue;
                cmd.toUpper();

                if (Ftp::SupportedCommand(cmd)) {
                    featReply->header.addEntry(e->clone());
                }

                if (cmd == cmdEprt())
                    hasEPRT = true;
                else if (cmd == cmdEpsv())
                    hasEPSV = true;
            }
        }
    } // else we got a FEAT error and will only report Squid-supported features

    char buf[256];
    if (!hasEPRT) {
        snprintf(buf, sizeof(buf), "\"%*s\"", prependSpaces + 4, "EPRT");
        featReply->header.putStr(HDR_FTP_PRE, buf);
    }
    if (!hasEPSV) {
        snprintf(buf, sizeof(buf), "\"%*s\"", prependSpaces + 4, "EPSV");
        featReply->header.putStr(HDR_FTP_PRE, buf);
    }

    featReply->header.refreshMask();

    writeForwardedReply(featReply.getRaw());
}
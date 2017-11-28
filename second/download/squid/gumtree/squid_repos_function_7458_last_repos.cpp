bool
Security::HandshakeParser::parseHello(const SBuf &data)
{
    try {
        if (!expectingModernRecords.configured())
            expectingModernRecords.configure(!isSslv2Record(data));

        // data contains everything read so far, but we may read more later
        tkRecords.reinput(data, true);
        tkRecords.rollback();
        while (!done)
            parseRecord();
        debugs(83, 7, "success; got: " << done);
        // we are done; tkRecords may have leftovers we are not interested in
        return true;
    }
    catch (const Parser::BinaryTokenizer::InsufficientInput &) {
        debugs(83, 5, "need more data");
        return false;
    }
    return false; // unreached
}
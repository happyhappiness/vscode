void
Security::HandshakeParser::parseRecord()
{
    if (expectingModernRecords)
        parseModernRecord();
    else
        parseVersion2Record();
}
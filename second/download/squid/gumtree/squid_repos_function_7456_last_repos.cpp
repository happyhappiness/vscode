SBuf
Security::HandshakeParser::parseSniExtension(const SBuf &extensionData) const
{
    // Servers SHOULD send an empty SNI extension, not an empty ServerNameList!
    if (extensionData.isEmpty())
        return SBuf();

    // SNI MUST NOT contain more than one name of the same name_type but
    // we ignore violations and simply return the first host name found.
    Parser::BinaryTokenizer tkList(extensionData);
    Parser::BinaryTokenizer tkNames(tkList.pstring16("ServerNameList"));
    while (!tkNames.atEnd()) {
        Parser::BinaryTokenizerContext serverName(tkNames, "ServerName");
        const uint8_t nameType = tkNames.uint8(".name_type");
        const SBuf name = tkNames.pstring16(".name");
        serverName.success();

        if (nameType == 0) {
            debugs(83, 3, "host_name=" << name);
            return name; // it may be empty
        }
        // else we just parsed a new/unsupported NameType which,
        // according to RFC 6066, MUST begin with a 16-bit length field
    }
    return SBuf(); // SNI extension lacks host_name
}
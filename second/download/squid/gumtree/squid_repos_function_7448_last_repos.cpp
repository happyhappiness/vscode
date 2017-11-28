void
Security::HandshakeParser::parseApplicationDataMessage()
{
    Must(currentContentType == ContentType::ctApplicationData);
    skipMessage("app data [fragment]");
}
void
Security::HandshakeParser::parseMessages()
{
    for (; !tkMessages.atEnd(); tkMessages.commit()) {
        switch (currentContentType) {
        case ContentType::ctChangeCipherSpec:
            parseChangeCipherCpecMessage();
            continue;
        case ContentType::ctAlert:
            parseAlertMessage();
            continue;
        case ContentType::ctHandshake:
            parseHandshakeMessage();
            continue;
        case ContentType::ctApplicationData:
            parseApplicationDataMessage();
            continue;
        }
        skipMessage("unknown ContentType msg [fragment]");
    }
}
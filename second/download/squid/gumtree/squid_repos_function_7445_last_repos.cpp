void
Security::HandshakeParser::parseChangeCipherCpecMessage()
{
    Must(currentContentType == ContentType::ctChangeCipherSpec);
    // We are currently ignoring Change Cipher Spec Protocol messages.
    skipMessage("ChangeCipherCpec msg [fragment]");

    // Everything after the ChangeCipherCpec message may be encrypted.
    // Continuing parsing is pointless. Stop here.
    resumingSession = true;
    done = "ChangeCipherCpec";
}
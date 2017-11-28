void
Security::HandshakeParser::parseExtensions(const SBuf &raw)
{
    Parser::BinaryTokenizer tk(raw);
    while (!tk.atEnd()) {
        Extension extension(tk);

        if (!details->unsupportedExtensions && !extension.supported()) {
            debugs(83, 5, "first unsupported extension: " << extension.type);
            details->unsupportedExtensions = true;
        }

        switch(extension.type) {
        case 0: // The SNI extension; RFC 6066, Section 3
            details->serverName = parseSniExtension(extension.data);
            break;
        case 5: // Certificate Status Request; RFC 6066, Section 8
            details->tlsStatusRequest = true;
            break;
        case 15: // The heartBeats, RFC 6520
            details->doHeartBeats = true;
            break;
        case 16: { // Application-Layer Protocol Negotiation Extension, RFC 7301
            Parser::BinaryTokenizer tkAPN(extension.data);
            details->tlsAppLayerProtoNeg = tkAPN.pstring16("APN");
            break;
        }
        case 35: // SessionTicket TLS Extension; RFC 5077
            details->tlsTicketsExtension = true;
            details->hasTlsTicket = !extension.data.isEmpty();
        case 13172: // Next Protocol Negotiation Extension (expired draft?)
        default:
            break;
        }
    }
}
void
Security::HandshakeParser::parseServerCertificates(const SBuf &raw)
{
    Parser::BinaryTokenizer tkList(raw);
    const SBuf clist = tkList.pstring24("CertificateList");
    Must(tkList.atEnd()); // no leftovers after all certificates

    Parser::BinaryTokenizer tkItems(clist);
    while (!tkItems.atEnd()) {
        Security::CertPointer cert;
        ParseCertificate(tkItems.pstring24("Certificate"), cert);
        serverCertificates.push_back(cert);
        debugs(83, 7, "parsed " << serverCertificates.size() << " certificates so far");
    }

}
void Adaptation::Icap::ModXact::handleUnknownScode()
{
    stopParsing();
    stopBackup();
    // TODO: mark connection as "bad"

    // Terminate the transaction; we do not know how to handle this response.
    throw TexcHere("Unsupported ICAP status code");
}
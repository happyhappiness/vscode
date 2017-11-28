int
Ssl::ServerBio::read(char *buf, int size, BIO *table)
{
    if (parsedHandshake) // done parsing TLS Hello
        return readAndGive(buf, size, table);
    else
        return readAndParse(buf, size, table);
}
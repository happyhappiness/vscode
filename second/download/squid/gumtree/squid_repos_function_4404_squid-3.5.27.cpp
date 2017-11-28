int
Ssl::ServerBio::read(char *buf, int size, BIO *table)
{
    return record_ ?
           readAndBuffer(buf, size, table, "TLS server Hello") : Ssl::Bio::read(buf, size, table);
}
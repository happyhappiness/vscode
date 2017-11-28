static int
squid_bio_read(BIO *table, char *buf, int size)
{
    Ssl::Bio *bio = static_cast<Ssl::Bio*>(BIO_get_data(table));
    assert(bio);
    return bio->read(buf, size, table);
}
static int
squid_bio_write(BIO *table, const char *buf, int size)
{
    Ssl::Bio *bio = static_cast<Ssl::Bio*>(BIO_get_data(table));
    assert(bio);
    return bio->write(buf, size, table);
}
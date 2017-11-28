static int
squid_bio_destroy(BIO *table)
{
    delete static_cast<Ssl::Bio*>(BIO_get_data(table));
    BIO_set_data(table, NULL);
    return 1;
}
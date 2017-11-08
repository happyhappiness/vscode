static BIO_METHOD *BIO_s_bucket(void)
{
    return &bio_bucket_method;
}
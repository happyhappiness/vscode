static BIO_METHOD *BIO_s_in_bucket(void)
{
    return &bio_bucket_in_method;
}
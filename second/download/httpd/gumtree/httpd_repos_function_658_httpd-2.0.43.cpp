static int bio_bucket_free(BIO *bio)
{
    if (bio == NULL) {
        return 0;
    }

    /* nothing to free here.
     * apache will destroy the bucket brigade for us
     */
    return 1;
}
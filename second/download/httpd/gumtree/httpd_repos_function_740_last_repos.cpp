static int bio_filter_destroy(BIO *bio)
{
    if (bio == NULL) {
        return 0;
    }

    /* nothing to free here.
     * apache will destroy the bucket brigade for us
     */
    return 1;
}
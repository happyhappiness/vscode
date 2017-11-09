void free_bio_methods(void)
{
    BIO_meth_free(bio_filter_out_method);
    BIO_meth_free(bio_filter_in_method);
}
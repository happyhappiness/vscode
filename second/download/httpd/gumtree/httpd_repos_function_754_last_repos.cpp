void init_bio_methods(void)
{
    bio_filter_out_method = BIO_meth_new(BIO_TYPE_MEM, "APR output filter");
    BIO_meth_set_write(bio_filter_out_method, &bio_filter_out_write);
    BIO_meth_set_read(bio_filter_out_method, &bio_filter_out_read); /* read is never called */
    BIO_meth_set_puts(bio_filter_out_method, &bio_filter_out_puts); /* puts is never called */
    BIO_meth_set_gets(bio_filter_out_method, &bio_filter_out_gets); /* gets is never called */
    BIO_meth_set_ctrl(bio_filter_out_method, &bio_filter_out_ctrl);
    BIO_meth_set_create(bio_filter_out_method, &bio_filter_create);
    BIO_meth_set_destroy(bio_filter_out_method, &bio_filter_destroy);

    bio_filter_in_method = BIO_meth_new(BIO_TYPE_MEM, "APR input filter");
    BIO_meth_set_write(bio_filter_in_method, &bio_filter_in_write); /* write is never called */
    BIO_meth_set_read(bio_filter_in_method, &bio_filter_in_read);
    BIO_meth_set_puts(bio_filter_in_method, &bio_filter_in_puts);   /* puts is never called */
    BIO_meth_set_gets(bio_filter_in_method, &bio_filter_in_gets);   /* gets is never called */
    BIO_meth_set_ctrl(bio_filter_in_method, &bio_filter_in_ctrl);   /* ctrl is never called */
    BIO_meth_set_create(bio_filter_in_method, &bio_filter_create);
    BIO_meth_set_destroy(bio_filter_in_method, &bio_filter_destroy);
}
int table_insert(table_t * table_p,
                 const void *key_buf, const int key_size,
                 const void *data_buf, const int data_size,
                 void **data_buf_p, const char overwrite_b)
{
    return table_insert_kd(table_p, key_buf, key_size, data_buf, data_size,
                           NULL, data_buf_p, overwrite_b);
}
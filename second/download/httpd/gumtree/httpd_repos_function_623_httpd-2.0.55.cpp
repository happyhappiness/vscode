table_t *table_alloc(const unsigned int bucket_n, int *error_p,
                 void *(*malloc_f)(void *opt_param, size_t size),
                 void *(*calloc_f)(void *opt_param, size_t number, size_t size),
                 void *(*realloc_f)(void *opt_param, void *ptr, size_t size),
                 void (*free_f)(void *opt_param, void *ptr), void *opt_param)
{
    table_t *table_p = NULL;
    unsigned int buck_n;

    /* allocate a table structure */
    if (malloc_f != NULL)
        table_p = malloc_f(opt_param, sizeof(table_t));
    else
        table_p = malloc(sizeof(table_t));
    if (table_p == NULL) {
        if (error_p != NULL)
            *error_p = TABLE_ERROR_ALLOC;
        return NULL;
    }

    if (bucket_n > 0)
        buck_n = bucket_n;
    else
        buck_n = DEFAULT_SIZE;
    /* allocate the buckets which are NULLed */
    if (calloc_f != NULL)
        table_p->ta_buckets = (table_entry_t **)calloc_f(opt_param, buck_n,
                                                       sizeof(table_entry_t *));
    else
        table_p->ta_buckets = (table_entry_t **)calloc(buck_n, sizeof(table_entry_t *));
    if (table_p->ta_buckets == NULL) {
        if (error_p != NULL)
            *error_p = TABLE_ERROR_ALLOC;
        if (free_f != NULL)
            free_f(opt_param, table_p);
        else
            free(table_p);
        return NULL;
    }

    /* initialize structure */
    table_p->ta_magic = TABLE_MAGIC;
    table_p->ta_flags = 0;
    table_p->ta_bucket_n = buck_n;
    table_p->ta_entry_n = 0;
    table_p->ta_data_align = 0;
    table_p->ta_linear.tl_magic = 0;
    table_p->ta_linear.tl_bucket_c = 0;
    table_p->ta_linear.tl_entry_c = 0;
    table_p->ta_file_size = 0;
    table_p->ta_malloc  = malloc_f  != NULL ? malloc_f  : sys_malloc;
    table_p->ta_calloc  = calloc_f  != NULL ? calloc_f  : sys_calloc;
    table_p->ta_realloc = realloc_f != NULL ? realloc_f : sys_realloc;
    table_p->ta_free    = free_f    != NULL ? free_f    : sys_free;
    table_p->opt_param = opt_param;

    if (error_p != NULL)
        *error_p = TABLE_ERROR_NONE;
    return table_p;
}
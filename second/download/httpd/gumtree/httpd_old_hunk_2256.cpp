
#ifdef SERVER_CONFIG_FILE
    printf(" -D SERVER_CONFIG_FILE=\"" SERVER_CONFIG_FILE "\"\n");
#endif
}

static void destroy_and_exit_process(process_rec *process,
                                     int process_exit_value)
{
    apr_pool_destroy(process->pool); /* and destroy all descendent pools */
    apr_terminate();
    exit(process_exit_value);
}

static process_rec *init_process(int *argc, const char * const * *argv)

static void destroy_and_exit_process(process_rec *process,
                                     int process_exit_value)
{
    apr_pool_destroy(process->pool); /* and destroy all descendent pools */
    apr_terminate();
    exit(process_exit_value);
}
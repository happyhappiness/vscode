
#ifdef SERVER_CONFIG_FILE
    printf(" -D SERVER_CONFIG_FILE=\"" SERVER_CONFIG_FILE "\"\n");
#endif
}

#define TASK_SWITCH_SLEEP 10000

static void destroy_and_exit_process(process_rec *process,
                                     int process_exit_value)
{
    /*
     * Sleep for TASK_SWITCH_SLEEP micro seconds to cause a task switch on
     * OS layer and thus give possibly started piped loggers a chance to
     * process their input. Otherwise it is possible that they get killed
     * by us before they can do so. In this case maybe valueable log messages
     * might get lost.
     */
    apr_sleep(TASK_SWITCH_SLEEP);
    apr_pool_destroy(process->pool); /* and destroy all descendent pools */
    apr_terminate();
    exit(process_exit_value);
}

static process_rec *init_process(int *argc, const char * const * *argv)

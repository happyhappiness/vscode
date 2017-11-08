int main(int argc, char **argv)
{
    apr_pool_t *pool;
    apr_port_t theport = 4747;

    printf("APR Test Application: echod\n");

    apr_initialize();
    atexit(apr_terminate);

    apr_pool_create(&pool, NULL);

    if (argc >= 2) {
        printf("argc = %d, port = '%s'\n", argc, argv[1]);
        theport = atoi(argv[1]);
    }

    fprintf(stdout, "Starting to listen on port %d\n", theport);
    glassToWall(theport, pool);

    return 0;
}
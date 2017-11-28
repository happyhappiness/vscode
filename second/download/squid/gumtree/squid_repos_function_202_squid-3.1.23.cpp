int
main(int argc, char *argv[])
{
    debug("ntlm_auth build " __DATE__ ", " __TIME__ " starting up...\n");

    my_program_name = argv[0];
    process_options(argc, argv);

    debug("options processed OK\n");

    /* initialize FDescs */
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    /* select the first domain controller we're going to use */
    current_dc = controllers;
    if (load_balance != 0 && numcontrollers > 1) {
        int n;
        pid_t pid = getpid();
        n = pid % numcontrollers;
        debug("load balancing. Selected controller #%d\n", n);
        while (n > 0) {
            current_dc = current_dc->next;
            n--;
        }
    }
    while (1) {
        manage_request();
    }
    return 0;
}
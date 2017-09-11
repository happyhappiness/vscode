/* main test, but callable from other files */
int quicklistTest(int argc, char *argv[]) {
    unsigned int err = 0;
    int optimize_start =
        -(int)(sizeof(optimization_level) / sizeof(*optimization_level));

    printf("Starting optimization offset at: %d\n", optimize_start);

    UNUSED(argc);
    UNUSED(argv);

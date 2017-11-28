int
main(int argc, char **argv)
{
    char buf[HELPER_INPUT_BUFFER];
    setbuf(stdout, NULL);
    ProcessArguments(argc, argv);
    while (fgets(buf, HELPER_INPUT_BUFFER, stdin) != NULL)
        DoOneRequest(buf);
    exit(0);
}
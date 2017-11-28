int
main(int argc, char **argv)
{
    char buf[256];
    setbuf(stdout, NULL);
    ProcessArguments(argc, argv);
    while (fgets(buf, 256, stdin) != NULL)
        DoOneRequest(buf);
    exit(0);
}
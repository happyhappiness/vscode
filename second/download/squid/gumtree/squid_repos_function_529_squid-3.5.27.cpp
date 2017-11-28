static void
ProcessArguments(int argc, char **argv)
{
    int i;
    i = LDAPArguments(argc, argv);
    if (i)
        exit(i);
}
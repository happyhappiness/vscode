void
init_mib(char *file)
{
    if (Mib != NULL)
        return;

    if (file != NULL)
        Mib = read_mib(file);
}
static void
usage(const char *program)
{
    fprintf(stderr, "Usage: %s [-D domain][-G][-c][-d][-h]\n"
            " -D    default user Domain\n"
            " -G    enable Active Directory Global group mode\n"
            " -c    use case insensitive compare (local mode only)\n"
            " -d    enable debugging\n"
            " -h    this message\n",
            program);
}
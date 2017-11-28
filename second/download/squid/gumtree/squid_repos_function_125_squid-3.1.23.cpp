static void
usage(char *program)
{
    fprintf(stderr, "Usage: %s [-D domain][-G][-P][-c][-d][-h]\n"
            " -D    default user Domain\n"
            " -G    enable Domain Global group mode\n"
            " -c    use case insensitive compare\n"
            " -d    enable debugging\n"
            " -h    this message\n",
            program);
}
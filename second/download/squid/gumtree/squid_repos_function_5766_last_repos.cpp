void
usage()
{
    fprintf(stderr,
            "Usage: %s [-d] [-v] [-h]\n"
            " -d  enable debugging.\n"
            " -v  enable verbose Negotiate packet debugging.\n"
            " -h  this message\n\n",
            my_program_name);
}
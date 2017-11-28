static void
usage(void)
{
    fprintf(stderr,
            "Usage: %s [-d] [-v] [-h]\n"
            " -d  enable debugging.\n"
            " -S  strip domain from username.\n"
            " -v  enable verbose NTLM packet debugging.\n"
            " -h  this message\n\n",
            my_program_name);
}
void
usage()
{
    fprintf(stderr,
            "%s usage:\n%s [-b] [-f] [-d] [-l] domain\\controller [domain\\controller ...]\n"
            "-b enables load-balancing among controllers\n"
            "-f enables failover among controllers (DEPRECATED and always active)\n"
            "-l changes behavior on domain controller failyures to last-ditch.\n"
            "-d enables debugging statements if DEBUG was defined at build-time.\n\n"
            "You MUST specify at least one Domain Controller.\n"
            "You can use either \\ or / as separator between the domain name \n"
            "and the controller name\n",
            my_program_name, my_program_name);
}
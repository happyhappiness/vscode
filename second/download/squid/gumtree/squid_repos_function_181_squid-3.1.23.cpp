void
usage()
{
    fprintf(stderr,
            "Usage: %s [-d] [-v] [-A|D LocalUserGroup] [-h]\n"
            " -d  enable debugging.\n"
            " -v  enable verbose NTLM packet debugging.\n"
            " -A  specify a Windows Local Group name allowed to authenticate\n"
            " -D  specify a Windows Local Group name not allowed to authenticate\n"
            " -h  this message\n\n",
            my_program_name);
}
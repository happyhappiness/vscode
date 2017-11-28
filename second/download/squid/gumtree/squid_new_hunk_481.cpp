/*
 * options:
 * -A can specify a Windows Local Group name allowed to authenticate.
 * -D can specify a Windows Local Group name not allowed to authenticate.
 * -O can specify the default Domain against to authenticate.
 */
static void
usage(const char *name)
{
    fprintf(stderr, "Usage:\n%s [-A|D UserGroup][-O DefaultDomain][-d]\n"
            "-A can specify a Windows Local Group name allowed to authenticate\n"
            "-D can specify a Windows Local Group name not allowed to authenticate\n"
            "-O can specify the default Domain against to authenticate\n"
            "-d enable debugging.\n"
            "-h this message\n\n",
            name);
}

void
process_options(int argc, char *argv[])
{
    int opt;

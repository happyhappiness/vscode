static void
usage(char *program)
{
    fprintf(stderr, "Usage: %s -g group1 [-g group2 ...] [-p] [-s]\n\n",
            program);
    fprintf(stderr, "-g group\n");
    fprintf(stderr,
            "			The group name or id that the user must belong in order to\n");
    fprintf(stderr,
            "			be allowed to authenticate.\n");
    fprintf(stderr,
            "-p			Verify primary user group as well\n");
    fprintf(stderr,
            "-s			Strip NT domain from usernames\n");
}
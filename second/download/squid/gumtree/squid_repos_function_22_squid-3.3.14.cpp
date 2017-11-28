static void
print_trailer(void)
{
    printf("<HR noshade size=\"1px\">\n");
    printf("<ADDRESS>\n");
    printf("Generated %s, by %s/%s@%s\n",
           mkrfc1123(now), progname, VERSION, getfullhostname());
    printf("</ADDRESS></BODY></HTML>\n");
}
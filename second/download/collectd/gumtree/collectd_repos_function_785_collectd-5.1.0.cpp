static void
free_domains ()
{
    int i;

    if (domains) {
        for (i = 0; i < nr_domains; ++i)
            virDomainFree (domains[i]);
        sfree (domains);
    }
    domains = NULL;
    nr_domains = 0;
}
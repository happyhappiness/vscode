static void
free_domains (void)
{
    if (domains) {
        for (int i = 0; i < nr_domains; ++i)
            virDomainFree (domains[i]);
        sfree (domains);
    }
    domains = NULL;
    nr_domains = 0;
}
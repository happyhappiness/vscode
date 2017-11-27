static int
add_domain (virDomainPtr dom)
{
    virDomainPtr *new_ptr;
    int new_size = sizeof (domains[0]) * (nr_domains+1);

    if (domains)
        new_ptr = realloc (domains, new_size);
    else
        new_ptr = malloc (new_size);

    if (new_ptr == NULL)
        return -1;

    domains = new_ptr;
    domains[nr_domains] = dom;
    return nr_domains++;
}
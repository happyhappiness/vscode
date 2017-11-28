static void
idnsFreeNameservers(void)
{
    safe_free(nameservers);
    nns = nns_alloc = 0;
}
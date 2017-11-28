void
fqdncacheFreeMemory(void)
{
    hashFreeItems(fqdn_table, fqdncacheFreeEntry);
    hashFreeMemory(fqdn_table);
    fqdn_table = NULL;
}
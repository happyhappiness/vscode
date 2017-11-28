void
clientdbFreeMemory(void)
{
    hashFreeItems(client_table, clientdbFreeItem);
    hashFreeMemory(client_table);
    client_table = NULL;
}
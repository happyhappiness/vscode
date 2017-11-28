static void
clientdbInit(void)
{
    if (client_table)
        return;

    client_table = hash_create((HASHCMP *) strcmp, CLIENT_DB_HASH_SIZE, hash_string);
}
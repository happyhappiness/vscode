static void
netdbHashDelete(const char *key)
{
    hash_link *hptr = (hash_link *)hash_lookup(addr_table, key);

    if (hptr == NULL) {
        debug_trap("netdbHashDelete: key not found");
        return;
    }

    hash_remove_link(addr_table, hptr);
}
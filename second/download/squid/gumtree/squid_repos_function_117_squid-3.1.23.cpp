int
dict_lookup (struct ip_user_dict *first_entry, char *username,
             char *address)
{
    /* Move the pointer to the first entry of the linked list. */
    struct ip_user_dict *current_entry = first_entry;

    while (current_entry->username != NULL) {
#ifdef DEBUG
        printf ("user: %s\naddr: %lu\nmask: %lu\n\n",
                current_entry->username, current_entry->address,
                current_entry->netmask);
#endif

        if ((inet_addr (address) & (unsigned long) current_entry->
                netmask) == current_entry->address) {
            /* If the username contains an @ we assume it´s a group and
               call the corresponding function */
            if ((strchr (current_entry->username, '@')) == NULL) {
                if ((match_user (current_entry->username, username)) == 1)
                    return 1;
            } else {
                if ((match_group (current_entry->username, username)) == 1)
                    return 1;
            }
        }
        current_entry = current_entry->next_entry;
    }

    /* If no match was found we return 0 */
    return 0;
}
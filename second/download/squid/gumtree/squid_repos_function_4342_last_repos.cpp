struct ip_user_dict *
load_dict(FILE * FH) {
    struct ip_user_dict *current_entry; /* the structure used to
                       store data */
    struct ip_user_dict *first_entry = NULL;    /* the head of the
                           linked list */
    char line[DICT_BUFFER_SIZE]; /* the buffer for the lines read
                   from the dict file */
    char *tmpbuf;           /* for the address before the
                   bitwise AND */

    /* the pointer to the first entry in the linked list */
    first_entry = static_cast<struct ip_user_dict*>(xmalloc(sizeof(struct ip_user_dict)));
    current_entry = first_entry;

    unsigned int lineCount = 0;
    while (fgets(line, sizeof(line), FH) != NULL) {
        ++lineCount;
        if (line[0] == '#') {
            continue;
        }

        char *cp; // a char pointer used to parse each line.
        if ((cp = strchr (line, '\n')) != NULL) {
            /* chop \n characters */
            *cp = '\0';
        }
        if (strtok(line, "\t ") != NULL) {
            // NP: line begins with IP/mask. Skipped to the end of it with this strtok()

            /* get the username */
            char *username;
            if ((username = strtok(NULL, "\t ")) == NULL) {
                debug("Missing username on line %u of dictionary file\n", lineCount);
                continue;
            }

            /* look for a netmask */
            if ((cp = strtok (line, "/")) != NULL) {
                /* store the ip address in a temporary buffer */
                tmpbuf = cp;
                cp = strtok (NULL, "/");
                if (cp != NULL) {
                    /* if we have a slash in the lhs, we have a netmask */
                    current_entry->netmask = (inet_addr(cp));
                    current_entry->address =
                        (((inet_addr (tmpbuf))) & current_entry->netmask);
                } else {
                    /* when theres no slash, we figure the netmask is /32 */
                    current_entry->address = (inet_addr(tmpbuf));
                    current_entry->netmask = (inet_addr("255.255.255.255"));
                }
            }
            /* get space for the username */
            current_entry->username =
                (char*)calloc(strlen(username) + 1, sizeof(char));
            strcpy(current_entry->username, username);

            /* get space and point current_entry to the new entry */
            current_entry->next_entry =
                static_cast<struct ip_user_dict*>(xmalloc(sizeof(struct ip_user_dict)));
            current_entry = current_entry->next_entry;
        }

    }

    /* Return a pointer to the first entry linked list */
    return first_entry;
}
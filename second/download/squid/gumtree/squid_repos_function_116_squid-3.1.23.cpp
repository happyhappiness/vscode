struct ip_user_dict *
load_dict (FILE * FH) {
    struct ip_user_dict *current_entry;	/* the structure used to
					   store data */
    struct ip_user_dict *first_entry = NULL;	/* the head of the
						   linked list */
    char line[BUFSIZE];		/* the buffer for the lines read
				   from the dict file */
    char *cp;			/* a char pointer used to parse
				   each line */
    char *username;		/* for the username */
    char *tmpbuf;			/* for the address before the
				   bitwise AND */

    /* the pointer to the first entry in the linked list */
    first_entry = malloc (sizeof (struct ip_user_dict));
    current_entry = first_entry;

    while ((cp = fgets (line, sizeof (line), FH)) != NULL) {
        if (line[0] == '#') {
            continue;
        }
        if ((cp = strchr (line, '\n')) != NULL) {
            /* chop \n characters */
            *cp = '\0';
        }
        if ((cp = strtok (line, "\t ")) != NULL) {
            /* get the username */
            username = strtok (NULL, "\t ");
            /* look for a netmask */
            if ((cp = strtok (line, "/")) != NULL) {
                /* store the ip address in a temporary buffer */
                tmpbuf = cp;
                cp = strtok (NULL, "/");
                if (cp != NULL) {
                    /* if we have a slash in the lhs, we have a netmask */
                    current_entry->netmask = (inet_addr (cp));
                    current_entry->address =
                        (((inet_addr (tmpbuf))) & current_entry->netmask);
                } else {
                    /* when theres no slash, we figure the netmask is /32 */
                    current_entry->address = (inet_addr (tmpbuf));
                    current_entry->netmask = (inet_addr ("255.255.255.255"));
                }
            }
            /* get space for the username */
            current_entry->username =
                calloc (strlen (username) + 1, sizeof (char));
            strcpy (current_entry->username, username);

            /* get space and point current_entry to the new entry */
            current_entry->next_entry =
                malloc (sizeof (struct ip_user_dict));
            current_entry = current_entry->next_entry;
        }

    }

    /* Return a pointer to the first entry linked list */
    return first_entry;
}
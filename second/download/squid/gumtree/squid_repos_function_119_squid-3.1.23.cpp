int
main (int argc, char *argv[])
{
    FILE *FH;
    char *filename = NULL;
    char *program_name = argv[0];
    char *cp;
    char *username, *address;
    char line[BUFSIZE];
    struct ip_user_dict *current_entry;
    int ch;

    setvbuf (stdout, NULL, _IOLBF, 0);
    while ((ch = getopt (argc, argv, "f:")) != -1) {
        switch (ch) {
        case 'f':
            filename = optarg;
            break;
        default:
            usage (program_name);
            exit (1);
        }
    }
    if (filename == NULL) {
        usage (program_name);
        exit(1);
    }
    FH = fopen (filename, "r");
    current_entry = load_dict (FH);

    while (fgets (line, sizeof (line), stdin)) {
        if ((cp = strchr (line, '\n')) == NULL) {
            /* too large message received.. skip and deny */
            fprintf(stderr, "%s: ERROR: Too large: %s\n", argv[0], line);
            while (fgets(line, sizeof(line), stdin)) {
                fprintf(stderr, "%s: ERROR: Too large..: %s\n", argv[0], line);
                if (strchr(line, '\n') != NULL)
                    break;
            }
            goto error;
        }
        *cp = '\0';
        address = strtok (line, " \t");
        username = strtok (NULL, " \t");
        if (!address || !username) {
            fprintf (stderr, "%s: unable to read tokens\n", argv[0]);
            goto error;
        }
        rfc1738_unescape(address);
        rfc1738_unescape(username);
#ifdef DEBUG
        printf ("result: %d\n",
                dict_lookup (current_entry, username, address));
#endif
        if ((dict_lookup (current_entry, username, address)) != 0) {
            printf ("OK\n");
        } else {
error:
            printf ("ERR\n");
        }
    }


    fclose (FH);
    return 0;
}
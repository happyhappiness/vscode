int
main (int argc, char *argv[])
{
    char *filename = NULL;
    char *program_name = argv[0];
    char *cp;
    char *username, *address;
    char line[HELPER_INPUT_BUFFER];
    struct ip_user_dict *current_entry;
    int ch;

    setvbuf (stdout, NULL, _IOLBF, 0);
    while ((ch = getopt(argc, argv, "df:h")) != -1) {
        switch (ch) {
        case 'f':
            filename = optarg;
            break;
        case 'd':
            debug_enabled = 1;
            break;
        case 'h':
            usage(program_name);
            exit (0);
        default:
            fprintf(stderr, "%s: FATAL: Unknown parameter option '%c'", program_name, ch);
            usage(program_name);
            exit (1);
        }
    }
    if (filename == NULL) {
        fprintf(stderr, "%s: FATAL: No Filename configured.", program_name);
        usage(program_name);
        exit(1);
    }
    FILE *FH = fopen(filename, "r");
    if (!FH) {
        fprintf(stderr, "%s: FATAL: Unable to open file '%s': %s", program_name, filename, xstrerror());
        exit(1);
    }
    current_entry = load_dict(FH);

    while (fgets(line, HELPER_INPUT_BUFFER, stdin)) {
        if ((cp = strchr (line, '\n')) == NULL) {
            /* too large message received.. skip and deny */
            fprintf(stderr, "%s: ERROR: Input Too Large: %s\n", program_name, line);
            while (fgets(line, sizeof(line), stdin)) {
                fprintf(stderr, "%s: ERROR: Input Too Large..: %s\n", program_name, line);
                if (strchr(line, '\n') != NULL)
                    break;
            }
            SEND_BH(HLP_MSG("Input Too Large."));
            continue;
        }
        *cp = '\0';
        address = strtok(line, " \t");
        username = strtok(NULL, " \t");
        if (!address || !username) {
            debug("%s: unable to read tokens\n", program_name);
            SEND_BH(HLP_MSG("Invalid Input."));
            continue;
        }
        rfc1738_unescape(address);
        rfc1738_unescape(username);
        int result = dict_lookup(current_entry, username, address);
        debug("%s: result: %d\n", program_name, result);
        if (result != 0) {
            SEND_OK("");
        } else {
            SEND_ERR("");
        }
    }

    fclose (FH);
    return 0;
}
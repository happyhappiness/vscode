static void cliOutputHelp(int argc, char **argv) {
    int i, len;
    struct commandHelp *help;
    int group = -1;

    if (argc == 0) {
        cliOutputGenericHelp();
        return;
    } else if (argc > 0 && argv[0][0] == '@') {
        len = sizeof(commandGroups)/sizeof(char*);
        for (i = 0; i < len; i++) {
            if (strcasecmp(argv[0]+1,commandGroups[i]) == 0) {
                group = i;
                break;
            }
        }
    }

    len = sizeof(commandHelp)/sizeof(struct commandHelp);
    assert(argc > 0);
    for (i = 0; i < len; i++) {
        help = &commandHelp[i];
        if (group == -1) {
            if (strcasecmp(help->name, argv[0]) == 0) {
                cliOutputCommandHelp(help,1);
            }
        } else {
            if (group == help->group) {
                cliOutputCommandHelp(help,0);
            }
        }
    }
    printf("\r\n");
}
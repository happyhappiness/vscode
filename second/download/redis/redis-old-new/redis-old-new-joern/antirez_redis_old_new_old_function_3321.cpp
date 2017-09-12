static void outputCommandHelp(struct commandHelp *help) {
    printf("\n  \x1b[1m%s\x1b[0m \x1b[90m%s\x1b[0m\n", help->name, help->params);
    printf("  \x1b[33msummary:\x1b[0m %s\n", help->summary);
    printf("  \x1b[33msince:\x1b[0m %s\n", help->since);
    printf("  \x1b[33mgroup:\x1b[0m %s\n", commandGroups[help->group]);
}
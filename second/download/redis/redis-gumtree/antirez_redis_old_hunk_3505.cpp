
/* Print generic help. */
static void cliOutputGenericHelp() {
    printf(
        "redis-cli %s\r\n"
        "Type: \"help @<group>\" to get a list of commands in <group>\r\n"
        "      \"help <command>\" for help on <command>\r\n"
        "      \"help <tab>\" to get a list of possible help topics\r\n"
        "      \"quit\" to exit\r\n",
        REDIS_VERSION
    );
}

/* Output all command help, filtering by group or command name. */

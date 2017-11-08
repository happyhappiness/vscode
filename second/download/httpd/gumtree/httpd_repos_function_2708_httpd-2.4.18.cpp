static int check_finalized(const sed_commands_t *commands)
{
    const sed_label_t *lab;
    if (commands->depth) {
        return 0;
    }

    /* Empty branch chain is not a issue */
    for (lab = commands->labtab + 1; lab < commands->lab; lab++) {
        if (lab->address == 0 || (lab->chain)) {
            return 0;
        }
    }
    return 1;
}
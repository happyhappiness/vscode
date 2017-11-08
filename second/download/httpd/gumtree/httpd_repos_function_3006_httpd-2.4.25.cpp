static sed_label_t *search(sed_commands_t *commands)
{
    sed_label_t *rp;
    sed_label_t *ptr;

    rp = commands->labtab;
    ptr = commands->lab;
    while (rp < ptr) {
        if (strcmp(rp->asc, ptr->asc) == 0)
            return rp;
        rp++;
    }

    return 0;
}
static void dechain(sed_label_t *lpt, sed_reptr_t *address)
{
    sed_reptr_t *rep;
    if ((lpt == NULL) || (lpt->chain == NULL) || (address == NULL))
        return;
    rep = lpt->chain;
    while (rep->lb1) {
        sed_reptr_t *next;

        next = rep->lb1;
        rep->lb1 = address;
        rep = next;
    }
    rep->lb1 = address;
    lpt->chain = NULL;
}
static void
free_node(struct node *np)
{
    struct enum_list *ep, *tep;

    ep = np->enums;
    while (ep) {
        tep = ep;
        ep = ep->next;
        xfree((char *) tep);
    }
    xfree((char *) np);
}
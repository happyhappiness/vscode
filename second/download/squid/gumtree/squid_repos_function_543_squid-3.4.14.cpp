static void
free_node_list(struct node *nl)
{
    while (nl) {
        struct node *t = nl->next;
        free_node(nl);
        nl = t;
    }
}
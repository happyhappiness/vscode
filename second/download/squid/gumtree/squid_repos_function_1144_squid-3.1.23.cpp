static void
free_http_port_list(http_port_list ** head)
{
    http_port_list *s;

    while ((s = *head) != NULL) {
        *head = s->next;
        cbdataReferenceDone(s);
    }
}
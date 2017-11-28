static struct wccp2_service_list_t *
wccp2_get_service_by_id(int service, int service_id) {

    struct wccp2_service_list_t *p;

    p = wccp2_service_list_head;

    while (p != NULL) {
        if (p->info.service == service && p->info.service_id == service_id) {
            return p;
        }

        p = p->next;
    }

    return NULL;
}
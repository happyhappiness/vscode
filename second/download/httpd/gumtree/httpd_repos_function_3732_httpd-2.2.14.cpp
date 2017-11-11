static void make_pollset(apr_pollset_t *pollset)
{
    int i;
    int pos = 0;

    pollset->num_read = 0;
    pollset->num_write = 0;
    pollset->num_except = 0;

    for (i = 0; i < pollset->nelts; i++) {
        if (pollset->query_set[i].reqevents & APR_POLLIN) {
            pollset->pollset[pos++] = pollset->query_set[i].desc.s->socketdes;
            pollset->num_read++;
        }
    }

    for (i = 0; i < pollset->nelts; i++) {
        if (pollset->query_set[i].reqevents & APR_POLLOUT) {
            pollset->pollset[pos++] = pollset->query_set[i].desc.s->socketdes;
            pollset->num_write++;
        }
    }

    for (i = 0; i < pollset->nelts; i++) {
        if (pollset->query_set[i].reqevents & APR_POLLPRI) {
            pollset->pollset[pos++] = pollset->query_set[i].desc.s->socketdes;
            pollset->num_except++;
        }
    }

    pollset->num_total = pollset->num_read + pollset->num_write + pollset->num_except;
}
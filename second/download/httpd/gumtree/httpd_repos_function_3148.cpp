static apr_status_t s_socket_add(void *user_baton,
                                 apr_pollfd_t *pfd,
                                 void *serf_baton)
{
    s_baton_t *s = (s_baton_t*)user_baton;
    /* XXXXX: recycle listener_poll_types */
    listener_poll_type *pt = malloc(sizeof(*pt));
    pt->type = PT_SERF;
    pt->baton = serf_baton;
    pfd->client_data = pt;
    return apr_pollset_add(s->pollset, pfd);
}
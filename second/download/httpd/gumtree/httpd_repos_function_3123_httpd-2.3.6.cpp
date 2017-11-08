static apr_status_t s_socket_remove(void *user_baton,
                                    apr_pollfd_t *pfd,
                                    void *serf_baton)
{
    s_baton_t *s = (s_baton_t*)user_baton;
    listener_poll_type *pt = pfd->client_data;
    free(pt);
    return apr_pollset_remove(s->pollset, pfd);
}
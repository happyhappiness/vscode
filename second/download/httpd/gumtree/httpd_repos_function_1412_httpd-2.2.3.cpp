static proxy_worker *find_route_worker(proxy_balancer *balancer,
                                       const char *route)
{
    int i;
    proxy_worker *worker = (proxy_worker *)balancer->workers->elts;
    for (i = 0; i < balancer->workers->nelts; i++) {
        if (*(worker->s->route) && strcmp(worker->s->route, route) == 0) {
            return worker;
        }
        worker++;
    }
    return NULL;
}
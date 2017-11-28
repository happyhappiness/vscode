static void
clientdbStartGC(void)
{
    max_clients = statCounter.client_http.clients;
    cleanup_running = 1;
    cleanup_removed = 0;
    clientdbGC(NULL);
}
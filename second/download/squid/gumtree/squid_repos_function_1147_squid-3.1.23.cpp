static void
free_https_port_list(https_port_list ** head)
{
    free_http_port_list((http_port_list**)head);
}
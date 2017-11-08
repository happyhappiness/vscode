static int
allowed_port(proxy_server_conf *conf, int port)
{
    int i;
    int *list = (int *) conf->allowed_connect_ports->elts;

    for(i = 0; i < conf->allowed_connect_ports->nelts; i++) {
	if(port == list[i])
	    return 1;
    }
    return 0;
}
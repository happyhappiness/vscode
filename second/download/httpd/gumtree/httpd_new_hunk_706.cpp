    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void *) &one,

		   sizeof(one)) == -1) {

#ifndef _OSD_POSIX /* BS2000 has this option "always on" */

	ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

		     "proxy: error setting reuseaddr option: setsockopt(SO_REUSEADDR)");

	ap_pclosesocket(p, sock);

	return HTTP_INTERNAL_SERVER_ERROR;

#endif /*_OSD_POSIX*/

    }



#ifdef SINIX_D_RESOLVER_BUG

    {

	struct in_addr *ip_addr = (struct in_addr *) *server_hp.h_addr_list;


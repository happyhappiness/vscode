

    /* Domain name must start with a '.' */

    if (addr[0] != '.')

	return 0;



    /* rfc1035 says DNS names must consist of "[-a-zA-Z0-9]" and '.' */

    for (i = 0; ap_isalnum(addr[i]) || addr[i] == '-' || addr[i] == '.'; ++i)

	continue;



#if 0

    if (addr[i] == ':') {

	fprintf(stderr, "@@@@ handle optional port in proxy_is_domainname()\n");

	/* @@@@ handle optional port */


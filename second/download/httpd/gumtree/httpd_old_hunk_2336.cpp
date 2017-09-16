	perror("Unable to gethostname");

	exit(1);

    }

    str[MAXHOSTNAMELEN] = '\0';

    if ((!(p = gethostbyname(str))) || (!(server_hostname = find_fqdn(a, p)))) {

	fprintf(stderr, "httpd: cannot determine local host name.\n");

	fprintf(stderr, "Use ServerName to set it manually.\n");

	exit(1);

    }



    return server_hostname;

}




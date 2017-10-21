				fprintf(stderr, "panic!\n");
				break;
			}
			if ((sp = getservbyname(servname, proto)) == NULL)
				ERR(EAI_SERVICE);
			port = sp->s_port;
			if (pai->ai_socktype == ANY)
				if (strcmp(sp->s_proto, "udp") == 0) {
					pai->ai_socktype = SOCK_DGRAM;
					pai->ai_protocol = IPPROTO_UDP;
				} else if (strcmp(sp->s_proto, "tcp") == 0) {
					pai->ai_socktype = SOCK_STREAM;
					pai->ai_protocol = IPPROTO_TCP;
				} else
					ERR(EAI_PROTOCOL);	/*xxx*/
		}
	}
	
	/*
	 * hostname == NULL.
	 * passive socket -> anyaddr (0.0.0.0 or ::)

	    /*
	     * assume username passwd already to be in colon separated form.
	     * Ready to be uu-encoded.
	     */
	    while (apr_isspace(*optarg))
		optarg++;
            if (apr_base64_encode_len(strlen(optarg)) > sizeof(tmp)) {
                err("Authentication credentials too long\n");
            }
	    l = apr_base64_encode(tmp, optarg, strlen(optarg));
	    tmp[l] = '\0';

            auth = apr_pstrcat(cntxt, auth, "Authorization: Basic ", tmp,
                               "\r\n", NULL);
	    break;
	case 'P':
	    /*
             * assume username passwd already to be in colon separated form.
             */
	    while (apr_isspace(*optarg))
		optarg++;
            if (apr_base64_encode_len(strlen(optarg)) > sizeof(tmp)) {
                err("Proxy credentials too long\n");
            }
	    l = apr_base64_encode(tmp, optarg, strlen(optarg));
	    tmp[l] = '\0';

            auth = apr_pstrcat(cntxt, auth, "Proxy-Authorization: Basic ",
                               tmp, "\r\n", NULL);
	    break;

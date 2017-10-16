      /* Telnet options */
      config->telnet_options =
        curl_slist_append(config->telnet_options, nextarg);
      break;
    case 'T':
      /* we are uploading */
      {
        struct getout *url;
        if(config->url_out || (config->url_out=config->url_list)) {
          /* there's a node here, if it already is filled-in continue to find
             an "empty" node */
          while(config->url_out && (config->url_out->flags&GETOUT_UPLOAD))
            config->url_out = config->url_out->next;
        }

        /* now there might or might not be an available node to fill in! */

        if(config->url_out)
          /* existing node */
          url = config->url_out;
        else
          /* there was no free node, create one! */
          url=new_getout(config);

        if(url) {
          url->flags |= GETOUT_UPLOAD; /* mark -T used */
          if(!*nextarg)
            url->flags |= GETOUT_NOUPLOAD;
          else {
            /* "-" equals stdin, but keep the string around for now */
            GetStr(&url->infile, nextarg);
          }
        }
      }
      break;
    case 'u':
      /* user:password  */
      GetStr(&config->userpwd, nextarg);
      cleanarg(nextarg);
      checkpasswd("host", &config->userpwd);
      break;
    case 'U':
      /* Proxy user:password  */
      GetStr(&config->proxyuserpwd, nextarg);
      cleanarg(nextarg);
      checkpasswd("proxy", &config->proxyuserpwd);
      break;
    case 'v':
      config->conf ^= CONF_VERBOSE; /* talk a lot */
      break;
    case 'V':
    {
      const char **proto;

      printf(CURL_ID "%s\n", curl_version());
      if (curlinfo->protocols) {
        printf("Protocols: ");
        for (proto=curlinfo->protocols; *proto; ++proto) {
          printf("%s ", *proto);
        }
        puts(""); /* newline */
      }
      if(curlinfo->features) {
        unsigned int i;
        struct feat {
          const char *name;
          int bitmask;
        };
        struct feat feats[] = {
          {"IPv6", CURL_VERSION_IPV6},
          {"krb4", CURL_VERSION_KERBEROS4},
          {"SSL",  CURL_VERSION_SSL},
          {"libz", CURL_VERSION_LIBZ},
          {"NTLM", CURL_VERSION_NTLM},
          {"GSS-Negotiate", CURL_VERSION_GSSNEGOTIATE},
          {"Debug", CURL_VERSION_DEBUG},
          {"AsynchDNS", CURL_VERSION_ASYNCHDNS},
          {"SPNEGO", CURL_VERSION_SPNEGO}
        };
        printf("Features: ");
        for(i=0; i<sizeof(feats)/sizeof(feats[0]); i++) {
          if(curlinfo->features & feats[i].bitmask)
            printf("%s ", feats[i].name);
        }
        puts(""); /* newline */
      }
    }
    return PARAM_HELP_REQUESTED;
    case 'w':
      /* get the output string */
      if('@' == *nextarg) {
        /* the data begins with a '@' letter, it means that a file name
           or - (stdin) follows */
        FILE *file;

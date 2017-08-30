

      if(!result) {

        char *host=(char *)"";

        const char *useragent="";

        const char *http = (conn->proxytype == CURLPROXY_HTTP_1_0) ?

          "1.0" : "1.1";

        bool ipv6_ip = conn->bits.ipv6_ip;

        char *hostheader;



        /* the hostname may be different */

        if(hostname != conn->host.name)

          ipv6_ip = (strchr(hostname, ':') != NULL);

        hostheader= /* host:port with IPv6 support */

          aprintf("%s%s%s:%hu", ipv6_ip?"[":"", hostname, ipv6_ip?"]":"",

                  remote_port);

        if(!hostheader) {

          Curl_add_buffer_free(req_buffer);


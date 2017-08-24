{
    /* Add the curl handles to our pollfds first */
    data=multi->easyp;
    while(data) {
      bitmap = multi_getsock(data, sockbunch, MAX_SOCKSPEREASYHANDLE);

      for(i=0; i< MAX_SOCKSPEREASYHANDLE; i++) {
        curl_socket_t s = CURL_SOCKET_BAD;

        if(bitmap & GETSOCK_READSOCK(i)) {
          ufds[nfds].fd = sockbunch[i];
          ufds[nfds].events = POLLIN;
          ++nfds;
          s = sockbunch[i];
        }
        if(bitmap & GETSOCK_WRITESOCK(i)) {
          ufds[nfds].fd = sockbunch[i];
          ufds[nfds].events = POLLOUT;
          ++nfds;
          s = sockbunch[i];
        }
        if(s == CURL_SOCKET_BAD) {
          break;
        }
      }

      data = data->next; /* check next handle */
    }
  }
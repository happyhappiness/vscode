f(SOCKET_ERROR == enum_netevents_func(sockfd, event_handle, &events)) {
        err = SOCKERRNO;
        if(err != EINPROGRESS) {
          infof(data, "WSAEnumNetworkEvents failed (%d)", err);
          keepon = FALSE;
          result = CURLE_READ_ERROR;
        }
        break;
      }
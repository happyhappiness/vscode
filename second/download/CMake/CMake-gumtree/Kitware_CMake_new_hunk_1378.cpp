      if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE,
                     data->set.device, strlen(data->set.device)+1) != 0) {
        /* printf("Failed to BINDTODEVICE, socket: %d  device: %s error: %s\n",
           sockfd, data->set.device, Curl_strerror(Curl_sockerrno())); */
        infof(data, "SO_BINDTODEVICE %s failed\n",
              data->set.device);
        /* This is typically "errno 1, error: Operation not permitted" if

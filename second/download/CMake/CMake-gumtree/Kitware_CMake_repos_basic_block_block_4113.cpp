f(Curl_printable_address(ai, buf, sizeof(buf)))
      printf("%s\n", buf);
    else
      printf("failed; %s\n", Curl_strerror(conn, SOCKERRNO))
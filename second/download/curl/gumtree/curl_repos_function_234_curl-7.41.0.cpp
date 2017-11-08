int main(void)
{
  CURL *curl;
  CURLcode res;
  struct sockaddr_in servaddr;  /*  socket address structure  */
  curl_socket_t sockfd;

#ifdef WIN32
  WSADATA wsaData;
  int initwsa;

  if((initwsa = WSAStartup(MAKEWORD(2,0), &wsaData)) != 0) {
    printf("WSAStartup failed: %d\n", initwsa);
    return 1;
  }
#endif

  curl = curl_easy_init();
  if(curl) {
    /*
     * Note that libcurl will internally think that you connect to the host
     * and port that you specify in the URL option.
     */
    curl_easy_setopt(curl, CURLOPT_URL, "http://99.99.99.99:9999");

    /* Create the socket "manually" */
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == CURL_SOCKET_BAD ) {
      printf("Error creating listening socket.\n");
      return 3;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(PORTNUM);

    if (INADDR_NONE == (servaddr.sin_addr.s_addr = inet_addr(IPADDR)))
      return 2;

    if(connect(sockfd,(struct sockaddr *) &servaddr, sizeof(servaddr)) ==
       -1) {
      close(sockfd);
      printf("client error: connect: %s\n", strerror(errno));
      return 1;
    }

    /* no progress meter please */
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

    /* send all data to this function  */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

    /* call this function to get a socket */
    curl_easy_setopt(curl, CURLOPT_OPENSOCKETFUNCTION, opensocket);
    curl_easy_setopt(curl, CURLOPT_OPENSOCKETDATA, &sockfd);

    /* call this function to set options for the socket */
    curl_easy_setopt(curl, CURLOPT_SOCKOPTFUNCTION, sockopt_callback);

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    if(res) {
      printf("libcurl error: %d\n", res);
      return 4;
    }
  }
  return 0;
}
  /* send short containing size of data packet */
  packet_size = htons((uint16_t)len);

  if (swrite(*sockfd, (void *)&packet_size, sizeof(packet_size)) != 0) {
    close(*sockfd);
    *sockfd = -1;
    return (-1);
  }

  /* send data packet */
  if (swrite(*sockfd, (void *)buff, len) != 0) {
    close(*sockfd);
    *sockfd = -1;
    return (-2);
  }

  return (0);
}

/* Get and print status from apcupsd NIS server */
static int apc_query_server(char const *node, char const *service,
                            apc_detail_t *apcups_detail) {
  int n;
  char recvline[1024];
  char *tokptr;
  char *toksaveptr;
  _Bool retry = 1;
  int status;

#if APCMAIN
#define PRINT_VALUE(name, val)                                                 \
  printf("  Found property: name = %s; value = %f;\n", name, val)
#else
#define PRINT_VALUE(name, val) /**/
#endif

  while (retry) {
    if (global_sockfd < 0) {
      global_sockfd = net_open(node, service);
      if (global_sockfd < 0) {
        ERROR("apcups plugin: Connecting to the "
              "apcupsd failed.");
        return (-1);
      }
    }

    status = net_send(&global_sockfd, "status", strlen("status"));
    if (status != 0) {
      /* net_send is closing the socket on error. */
      assert(global_sockfd < 0);
      if (retry) {
        retry = 0;
        count_retries++;
        continue;
      }

      ERROR("apcups plugin: Writing to the socket failed.");
      return (-1);
    }

    break;
  } /* while (retry) */

  /* When collectd's collection interval is larger than apcupsd's
   * timeout, we would have to retry / re-connect each iteration. Try to
   * detect this situation and shut down the socket gracefully in that
   * case. Otherwise, keep the socket open to avoid overhead. */
  count_iterations++;

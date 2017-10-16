  if(curlx_strequal("active", str))
    return CURLFTPSSL_CCC_ACTIVE;
  warnf(config, "unrecognized ftp CCC method '%s', using default\n", str);
  return CURLFTPSSL_CCC_PASSIVE;
}


static int sockoptcallback(void *clientp, curl_socket_t curlfd,
                           curlsocktype purpose)
{
  struct Configurable *config = (struct Configurable *)clientp;
  int onoff = 1; /* this callback is only used if we ask for keepalives on the
                    connection */
#if defined(TCP_KEEPIDLE) || defined(TCP_KEEPINTVL)
  int keepidle = (int)config->alivetime;
#endif

  switch (purpose) {
  case CURLSOCKTYPE_IPCXN:
    if(setsockopt(curlfd, SOL_SOCKET, SO_KEEPALIVE, (void *)&onoff,
                  sizeof(onoff)) < 0) {
      /* don't abort operation, just issue a warning */
      SET_SOCKERRNO(0);
      warnf(clientp, "Could not set SO_KEEPALIVE!\n");
      return 0;
    }
    else {
      if (config->alivetime) {
#ifdef TCP_KEEPIDLE
        if(setsockopt(curlfd, IPPROTO_TCP, TCP_KEEPIDLE, (void *)&keepidle,
                      sizeof(keepidle)) < 0) {
          /* don't abort operation, just issue a warning */
          SET_SOCKERRNO(0);
          warnf(clientp, "Could not set TCP_KEEPIDLE!\n");
          return 0;
        }
#endif
#ifdef TCP_KEEPINTVL
        if(setsockopt(curlfd, IPPROTO_TCP, TCP_KEEPINTVL, (void *)&keepidle,
                      sizeof(keepidle)) < 0) {
          /* don't abort operation, just issue a warning */
          SET_SOCKERRNO(0);
          warnf(clientp, "Could not set TCP_KEEPINTVL!\n");
          return 0;
        }
#endif
      }
    }
    break;
  default:
    break;
  }

  return 0;
}


static ParameterError getparameter(char *flag, /* f or -long-flag */
                                   char *nextarg, /* NULL if unset */
                                   bool *usedarg, /* set to TRUE if the arg
                                                     has been used */
                                   struct Configurable *config)
{

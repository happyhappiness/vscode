static int camqp_connect(camqp_config_t *conf) /* {{{ */
{
  static time_t last_connect_time = 0;

  amqp_rpc_reply_t reply;
  int status;
#ifdef HAVE_AMQP_TCP_SOCKET
  amqp_socket_t *socket;
#else
  int sockfd;
#endif

  if (conf->connection != NULL)
    return (0);

  time_t now = time(NULL);
  if (now < (last_connect_time + conf->connection_retry_delay)) {
    DEBUG("amqp plugin: skipping connection retry, "
          "ConnectionRetryDelay: %d",
          conf->connection_retry_delay);
    return (1);
  } else {
    DEBUG("amqp plugin: retrying connection");
    last_connect_time = now;
  }

  conf->connection = amqp_new_connection();
  if (conf->connection == NULL) {
    ERROR("amqp plugin: amqp_new_connection failed.");
    return (ENOMEM);
  }

#ifdef HAVE_AMQP_TCP_SOCKET
#define CLOSE_SOCKET() /* amqp_destroy_connection() closes the socket for us   \
                          */
  /* TODO: add support for SSL using amqp_ssl_socket_new
   *       and related functions */
  socket = amqp_tcp_socket_new(conf->connection);
  if (!socket) {
    ERROR("amqp plugin: amqp_tcp_socket_new failed.");
    amqp_destroy_connection(conf->connection);
    conf->connection = NULL;
    return (ENOMEM);
  }

  status = amqp_socket_open(socket, CONF(conf, host), conf->port);
  if (status < 0) {
    char errbuf[1024];
    status *= -1;
    ERROR("amqp plugin: amqp_socket_open failed: %s",
          sstrerror(status, errbuf, sizeof(errbuf)));
    amqp_destroy_connection(conf->connection);
    conf->connection = NULL;
    return (status);
  }
#else /* HAVE_AMQP_TCP_SOCKET */
#define CLOSE_SOCKET() close(sockfd)
  /* this interface is deprecated as of rabbitmq-c 0.4 */
  sockfd = amqp_open_socket(CONF(conf, host), conf->port);
  if (sockfd < 0) {
    char errbuf[1024];
    status = (-1) * sockfd;
    ERROR("amqp plugin: amqp_open_socket failed: %s",
          sstrerror(status, errbuf, sizeof(errbuf)));
    amqp_destroy_connection(conf->connection);
    conf->connection = NULL;
    return (status);
  }
  amqp_set_sockfd(conf->connection, sockfd);
#endif

  reply = amqp_login(conf->connection, CONF(conf, vhost),
                     /* channel max = */ 0,
                     /* frame max   = */ 131072,
                     /* heartbeat   = */ 0,
                     /* authentication = */ AMQP_SASL_METHOD_PLAIN,
                     CONF(conf, user), CONF(conf, password));
  if (reply.reply_type != AMQP_RESPONSE_NORMAL) {
    ERROR("amqp plugin: amqp_login (vhost = %s, user = %s) failed.",
          CONF(conf, vhost), CONF(conf, user));
    amqp_destroy_connection(conf->connection);
    CLOSE_SOCKET();
    conf->connection = NULL;
    return (1);
  }

  amqp_channel_open(conf->connection, /* channel = */ 1);
  /* FIXME: Is checking "reply.reply_type" really correct here? How does
   * it get set? --octo */
  if (reply.reply_type != AMQP_RESPONSE_NORMAL) {
    ERROR("amqp plugin: amqp_channel_open failed.");
    amqp_connection_close(conf->connection, AMQP_REPLY_SUCCESS);
    amqp_destroy_connection(conf->connection);
    CLOSE_SOCKET();
    conf->connection = NULL;
    return (1);
  }

  INFO("amqp plugin: Successfully opened connection to vhost \"%s\" "
       "on %s:%i.",
       CONF(conf, vhost), CONF(conf, host), conf->port);

  status = camqp_create_exchange(conf);
  if (status != 0)
    return (status);

  if (!conf->publish)
    return (camqp_setup_queue(conf));
  return (0);
}
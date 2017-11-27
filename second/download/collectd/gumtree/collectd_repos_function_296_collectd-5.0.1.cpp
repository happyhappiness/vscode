static void camqp_close_connection (camqp_config_t *conf) /* {{{ */
{
    int sockfd;

    if ((conf == NULL) || (conf->connection == NULL))
        return;

    sockfd = amqp_get_sockfd (conf->connection);
    amqp_channel_close (conf->connection, CAMQP_CHANNEL, AMQP_REPLY_SUCCESS);
    amqp_connection_close (conf->connection, AMQP_REPLY_SUCCESS);
    amqp_destroy_connection (conf->connection);
    close (sockfd);
    conf->connection = NULL;
}
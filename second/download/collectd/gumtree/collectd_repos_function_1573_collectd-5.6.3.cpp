static int wrr_notification(const notification_t *n, user_data_t *ud) /* {{{ */
{
  int status;
  struct riemann_host *host = ud->data;
  riemann_message_t *msg;

  if (!host->notifications)
    return 0;

  /*
   * Never batch for notifications, send them ASAP
   */
  msg = wrr_notification_to_message(host, n);
  if (msg == NULL)
    return (-1);

  status = wrr_send(host, msg);
  if (status != 0)
    c_complain(
        LOG_ERR, &host->init_complaint,
        "write_riemann plugin: riemann_client_send failed with status %i",
        status);
  else
    c_release(LOG_DEBUG, &host->init_complaint,
              "write_riemann plugin: riemann_client_send succeeded");

  riemann_message_free(msg);
  return (status);
}
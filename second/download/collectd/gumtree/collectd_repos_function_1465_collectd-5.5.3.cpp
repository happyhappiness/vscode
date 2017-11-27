static int riemann_notification(const notification_t *n, user_data_t *ud) /* {{{ */
{
	int			 status;
	struct riemann_host	*host = ud->data;
	Msg			*msg;

	if (!host->notifications)
		return 0;

    /*
     * Never batch for notifications, send them ASAP
     */
	msg = riemann_notification_to_protobuf (host, n);
	if (msg == NULL)
		return (-1);

	status = riemann_send (host, msg);
	if (status != 0)
		ERROR ("write_riemann plugin: riemann_send failed with status %i",
				status);

	riemann_msg_protobuf_free (msg);
	return (status);
}
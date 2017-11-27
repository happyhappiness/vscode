static int riemann_write(const data_set_t *ds, /* {{{ */
	      const value_list_t *vl,
	      user_data_t *ud)
{
	int			 status = 0;
	int			 statuses[vl->values_len];
	struct riemann_host	*host = ud->data;
	Msg			*msg;

	if (host->check_thresholds)
		write_riemann_threshold_check(ds, vl, statuses);

    if (host->use_tcp == 1 && host->batch_mode) {

        riemann_batch_add_value_list (host, ds, vl, statuses);


    } else {

        msg = riemann_value_list_to_protobuf (host, ds, vl, statuses);
        if (msg == NULL)
            return (-1);

        status = riemann_send (host, msg);
        if (status != 0)
            ERROR ("write_riemann plugin: riemann_send failed with status %i",
                   status);

        riemann_msg_protobuf_free (msg);
    }
	return status;
}
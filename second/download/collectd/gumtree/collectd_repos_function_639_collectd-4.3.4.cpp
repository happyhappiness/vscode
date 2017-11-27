static int ntpd_send_request (int req_code, int req_items, int req_size, char *req_data)
{
	int             sd;
	struct req_pkt  req;
	size_t          req_data_len;
	int             status;

	assert (req_items >= 0);
	assert (req_size  >= 0);

	if ((sd = ntpd_connect ()) < 0)
		return (-1);

	memset ((void *) &req, '\0', sizeof (req));
	req.rm_vn_mode = RM_VN_MODE(0, 0, 0);
	req.auth_seq   = AUTH_SEQ (0, 0);
	req.implementation = IMPL_XNTPD;
	req.request = (unsigned char) req_code;

	req_data_len = (size_t) (req_items * req_size);

	assert (((req_data != NULL) && (req_data_len > 0))
			|| ((req_data == NULL) && (req_items == 0) && (req_size == 0)));

	req.err_nitems   = ERR_NITEMS (0, req_items);
	req.mbz_itemsize = MBZ_ITEMSIZE (req_size);
	
	if (req_data != NULL)
		memcpy ((void *) req.data, (const void *) req_data, req_data_len);

	DEBUG ("req_items = %i; req_size = %i; req_data = %p;",
			req_items, req_size, (void *) req_data);

	status = swrite (sd, (const char *) &req, REQ_LEN_NOMAC);
	if (status < 0)
	{
		DEBUG ("`swrite' failed. Closing socket #%i", sd);
		close (sd);
		sock_descr = sd = -1;
		return (status);
	}

	return (0);
}
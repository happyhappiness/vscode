static void dns_child_callback (const rfc1035_header_t *dns)
{
	if (dns->qr == 0)
	{
		/* This is a query */
		pthread_mutex_lock (&traffic_mutex);
		tr_queries += dns->length;
		pthread_mutex_unlock (&traffic_mutex);

		pthread_mutex_lock (&qtype_mutex);
		counter_list_add (&qtype_list,  dns->qtype,  1);
		pthread_mutex_unlock (&qtype_mutex);
	}
	else
	{
		/* This is a reply */
		pthread_mutex_lock (&traffic_mutex);
		tr_responses += dns->length;
		pthread_mutex_unlock (&traffic_mutex);

		pthread_mutex_lock (&rcode_mutex);
		counter_list_add (&rcode_list,  dns->rcode,  1);
		pthread_mutex_unlock (&rcode_mutex);
	}

	/* FIXME: Are queries, replies or both interesting? */
	pthread_mutex_lock (&opcode_mutex);
	counter_list_add (&opcode_list, dns->opcode, 1);
	pthread_mutex_unlock (&opcode_mutex);
}
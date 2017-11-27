static int dns_read (void)
{
	unsigned int keys[T_MAX];
	unsigned int values[T_MAX];
	int len;

	counter_list_t *ptr;

	pthread_mutex_lock (&traffic_mutex);
	values[0] = tr_queries;
	values[1] = tr_responses;
	pthread_mutex_unlock (&traffic_mutex);

	if ((values[0] != 0) || (values[1] != 0))
		submit_octets (values[0], values[1]);

	pthread_mutex_lock (&qtype_mutex);
	for (ptr = qtype_list, len = 0;
		       	(ptr != NULL) && (len < T_MAX);
		       	ptr = ptr->next, len++)
	{
		keys[len]   = ptr->key;
		values[len] = ptr->value;
	}
	pthread_mutex_unlock (&qtype_mutex);

	for (int i = 0; i < len; i++)
	{
		DEBUG ("dns plugin: qtype = %u; counter = %u;", keys[i], values[i]);
		submit_derive ("dns_qtype", qtype_str (keys[i]), values[i]);
	}

	pthread_mutex_lock (&opcode_mutex);
	for (ptr = opcode_list, len = 0;
		       	(ptr != NULL) && (len < T_MAX);
		       	ptr = ptr->next, len++)
	{
		keys[len]   = ptr->key;
		values[len] = ptr->value;
	}
	pthread_mutex_unlock (&opcode_mutex);

	for (int i = 0; i < len; i++)
	{
		DEBUG ("dns plugin: opcode = %u; counter = %u;", keys[i], values[i]);
		submit_derive ("dns_opcode", opcode_str (keys[i]), values[i]);
	}

	pthread_mutex_lock (&rcode_mutex);
	for (ptr = rcode_list, len = 0;
		       	(ptr != NULL) && (len < T_MAX);
		       	ptr = ptr->next, len++)
	{
		keys[len]   = ptr->key;
		values[len] = ptr->value;
	}
	pthread_mutex_unlock (&rcode_mutex);

	for (int i = 0; i < len; i++)
	{
		DEBUG ("dns plugin: rcode = %u; counter = %u;", keys[i], values[i]);
		submit_derive ("dns_rcode", rcode_str (keys[i]), values[i]);
	}

	return (0);
}
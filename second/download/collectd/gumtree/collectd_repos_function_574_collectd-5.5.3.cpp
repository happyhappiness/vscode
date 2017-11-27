static int sensu_write(const data_set_t *ds, /* {{{ */
	      const value_list_t *vl,
	      user_data_t *ud)
{
	int status = 0;
	int statuses[vl->values_len];
	struct sensu_host	*host = ud->data;
	gauge_t *rates = NULL;
	int i;
	char *msg;

	pthread_mutex_lock(&host->lock);
	memset(statuses, 0, vl->values_len * sizeof(*statuses));

	if (host->store_rates) {
		rates = uc_get_rate(ds, vl);
		if (rates == NULL) {
			ERROR("write_sensu plugin: uc_get_rate failed.");
			pthread_mutex_unlock(&host->lock);
			return -1;
		}
	}
	for (i = 0; i < (size_t) vl->values_len; i++) {
		msg = sensu_value_to_json(host, ds, vl, (int) i, rates, statuses[i]);
		if (msg == NULL) {
			sfree(rates);
			pthread_mutex_unlock(&host->lock);
			return -1;
		}
		status = sensu_send(host, msg);
		free(msg);
		if (status != 0) {
			ERROR("write_sensu plugin: sensu_send failed with status %i", status);
			pthread_mutex_unlock(&host->lock);
			sfree(rates);
			return status;
		}
	}
	sfree(rates);
	pthread_mutex_unlock(&host->lock);
	return status;
}
static int fc_create (int type, const oconfig_item_t *ci, void **user_data)
{
	pfc_user_data_t *data;

	int ret = 0;

	dTHX;

	if (NULL == perl_threads)
		return 0;

	if (NULL == aTHX) {
		c_ithread_t *t = NULL;

		pthread_mutex_lock (&perl_threads->mutex);
		t = c_ithread_create (perl_threads->head->interp);
		pthread_mutex_unlock (&perl_threads->mutex);

		aTHX = t->interp;
	}

	log_debug ("fc_create: c_ithread: interp = %p (active threads: %i)",
			aTHX, perl_threads->number_of_threads);

	if ((1 != ci->values_num)
			|| (OCONFIG_TYPE_STRING != ci->values[0].type)) {
		log_warn ("A \"%s\" block expects a single string argument.",
				(FC_MATCH == type) ? "Match" : "Target");
		return -1;
	}

	data = (pfc_user_data_t *)smalloc (sizeof (*data));
	data->name      = sstrdup (ci->values[0].value.string);
	data->user_data = newSV (0);

	ret = fc_call (aTHX_ type, FC_CB_CREATE, data, ci);

	if (0 != ret)
		PFC_USER_DATA_FREE (data);
	else
		*user_data = data;
	return ret;
}
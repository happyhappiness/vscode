static int email_read (void)
{
	type_t *ptr;

	double score_old;
	int score_count_old;

	static type_list_t *cnt;
	static type_list_t *sz;
	static type_list_t *chk;

	if (disabled)
		return (-1);

	if (NULL == cnt) {
		cnt = (type_list_t *)smalloc (sizeof (type_list_t));
		cnt->head = NULL;
	}

	if (NULL == sz) {
		sz = (type_list_t *)smalloc (sizeof (type_list_t));
		sz->head = NULL;
	}

	if (NULL == chk) {
		chk = (type_list_t *)smalloc (sizeof (type_list_t));
		chk->head = NULL;
	}

	/* email count */
	pthread_mutex_lock (&count_mutex);

	copy_type_list (&count, cnt);

	pthread_mutex_unlock (&count_mutex);

	for (ptr = cnt->head; NULL != ptr; ptr = ptr->next) {
		email_submit ("email_count", ptr->name, ptr->value);
	}

	/* email size */
	pthread_mutex_lock (&size_mutex);

	copy_type_list (&size, sz);

	pthread_mutex_unlock (&size_mutex);

	for (ptr = sz->head; NULL != ptr; ptr = ptr->next) {
		email_submit ("email_size", ptr->name, ptr->value);
	}

	/* spam score */
	pthread_mutex_lock (&score_mutex);

	score_old = score;
	score_count_old = score_count;
	score = 0.0;
	score_count = 0;

	pthread_mutex_unlock (&score_mutex);

	if (score_count_old > 0)
		email_submit ("spam_score", "", score_old);

	/* spam checks */
	pthread_mutex_lock (&check_mutex);

	copy_type_list (&check, chk);

	pthread_mutex_unlock (&check_mutex);

	for (ptr = chk->head; NULL != ptr; ptr = ptr->next)
		email_submit ("spam_check", ptr->name, ptr->value);

	return (0);
}
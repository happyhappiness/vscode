static void cache_flush (int max_age)
{
	value_cache_t *this;
	value_cache_t *prev;
	time_t now;

	pthread_mutex_lock (&cache_lock);

	now = time (NULL);

	if ((now - cache_oldest) <= max_age)
	{
		pthread_mutex_unlock (&cache_lock);
		return;
	}
	
	cache_oldest = now;

	prev = NULL;
	this = cache_head;

	while (this != NULL)
	{
		if ((now - this->time) <= max_age)
		{
			if (this->time < cache_oldest)
				cache_oldest = this->time;

			prev = this;
			this = this->next;
			continue;
		}

		if (prev == NULL)
			cache_head = this->next;
		else
			prev->next = this->next;

		free (this->gauge);
		free (this->counter);
		free (this);

		if (prev == NULL)
			this = cache_head;
		else
			this = prev->next;
	} /* while (this != NULL) */

	pthread_mutex_unlock (&cache_lock);
}
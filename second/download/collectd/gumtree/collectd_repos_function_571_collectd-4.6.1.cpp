static c_ithread_t *c_ithread_create (PerlInterpreter *base)
{
	c_ithread_t *t = NULL;
	dTHXa (NULL);

	assert (NULL != perl_threads);

	t = (c_ithread_t *)smalloc (sizeof (c_ithread_t));
	memset (t, 0, sizeof (c_ithread_t));

	t->interp = (NULL == base)
		? NULL
		: perl_clone (base, CLONEf_KEEP_PTR_TABLE);

	aTHX = t->interp;

	if ((NULL != base) && (NULL != PL_endav)) {
		av_clear (PL_endav);
		av_undef (PL_endav);
		PL_endav = Nullav;
	}

#if COLLECT_DEBUG
	++perl_threads->number_of_threads;
#endif /* COLLECT_DEBUG */

	t->next = NULL;

	if (NULL == perl_threads->tail) {
		perl_threads->head = t;
		t->prev = NULL;
	}
	else {
		perl_threads->tail->next = t;
		t->prev = perl_threads->tail;
	}

	perl_threads->tail = t;

	pthread_setspecific (perl_thr_key, (const void *)t);
	return t;
}
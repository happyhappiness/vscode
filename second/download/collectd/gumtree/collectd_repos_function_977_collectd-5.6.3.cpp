static void c_ithread_destroy(c_ithread_t *ithread) {
  dTHXa(ithread->interp);

  assert(NULL != perl_threads);

  PERL_SET_CONTEXT(aTHX);
  log_debug("Shutting down Perl interpreter %p...", aTHX);

#if COLLECT_DEBUG
  sv_report_used();

  --perl_threads->number_of_threads;
#endif /* COLLECT_DEBUG */

  perl_destruct(aTHX);
  perl_free(aTHX);

  if (NULL == ithread->prev)
    perl_threads->head = ithread->next;
  else
    ithread->prev->next = ithread->next;

  if (NULL == ithread->next)
    perl_threads->tail = ithread->prev;
  else
    ithread->next->prev = ithread->prev;

  sfree(ithread);
  return;
}
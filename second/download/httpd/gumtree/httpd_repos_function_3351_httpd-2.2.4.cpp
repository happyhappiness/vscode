static void apr_thread_begin(void *arg)
{
  apr_thread_t *thread = (apr_thread_t *)arg;
  thread->exitval = thread->func(thread, thread->data);
}
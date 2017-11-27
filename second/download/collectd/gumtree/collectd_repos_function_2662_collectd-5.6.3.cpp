int plugin_thread_create(pthread_t *thread, const pthread_attr_t *attr,
                         void *(*start_routine)(void *), void *arg) {
  plugin_thread_t *plugin_thread;

  plugin_thread = malloc(sizeof(*plugin_thread));
  if (plugin_thread == NULL)
    return -1;

  plugin_thread->ctx = plugin_get_ctx();
  plugin_thread->start_routine = start_routine;
  plugin_thread->arg = arg;

  return pthread_create(thread, attr, plugin_thread_start, plugin_thread);
}
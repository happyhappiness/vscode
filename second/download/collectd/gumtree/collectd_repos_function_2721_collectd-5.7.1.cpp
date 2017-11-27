static int plugin_insert_read(read_func_t *rf) {
  int status;
  llentry_t *le;

  rf->rf_next_read = cdtime();
  rf->rf_effective_interval = rf->rf_interval;

  pthread_mutex_lock(&read_lock);

  if (read_list == NULL) {
    read_list = llist_create();
    if (read_list == NULL) {
      pthread_mutex_unlock(&read_lock);
      ERROR("plugin_insert_read: read_list failed.");
      return (-1);
    }
  }

  if (read_heap == NULL) {
    read_heap = c_heap_create(plugin_compare_read_func);
    if (read_heap == NULL) {
      pthread_mutex_unlock(&read_lock);
      ERROR("plugin_insert_read: c_heap_create failed.");
      return (-1);
    }
  }

  le = llist_search(read_list, rf->rf_name);
  if (le != NULL) {
    pthread_mutex_unlock(&read_lock);
    WARNING("The read function \"%s\" is already registered. "
            "Check for duplicate \"LoadPlugin\" lines "
            "in your configuration!",
            rf->rf_name);
    return (EINVAL);
  }

  le = llentry_create(rf->rf_name, rf);
  if (le == NULL) {
    pthread_mutex_unlock(&read_lock);
    ERROR("plugin_insert_read: llentry_create failed.");
    return (-1);
  }

  status = c_heap_insert(read_heap, rf);
  if (status != 0) {
    pthread_mutex_unlock(&read_lock);
    ERROR("plugin_insert_read: c_heap_insert failed.");
    llentry_destroy(le);
    return (-1);
  }

  /* This does not fail. */
  llist_append(read_list, le);

  /* Wake up all the read threads. */
  pthread_cond_broadcast(&read_cond);
  pthread_mutex_unlock(&read_lock);
  return (0);
}
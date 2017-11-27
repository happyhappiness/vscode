int plugin_unregister_read_group(const char *group) /* {{{ */
{
  llentry_t *le;
  read_func_t *rf;

  int found = 0;

  if (group == NULL)
    return -ENOENT;

  pthread_mutex_lock(&read_lock);

  if (read_list == NULL) {
    pthread_mutex_unlock(&read_lock);
    return -ENOENT;
  }

  while (42) {
    le = llist_search_custom(read_list, compare_read_func_group, (void *)group);

    if (le == NULL)
      break;

    ++found;

    llist_remove(read_list, le);

    rf = le->value;
    assert(rf != NULL);
    rf->rf_type = RF_REMOVE;

    llentry_destroy(le);

    DEBUG("plugin_unregister_read_group: "
          "Marked `%s' (group `%s') for removal.",
          rf->rf_name, group);
  }

  pthread_mutex_unlock(&read_lock);

  if (found == 0) {
    WARNING("plugin_unregister_read_group: No such "
            "group of read function: %s",
            group);
    return -ENOENT;
  }

  return 0;
}
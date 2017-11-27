static void c_ipmi_free_instance(c_ipmi_instance_t *st) {
  if (st == NULL)
    return;

  assert(st->next == NULL);

  sfree(st->name);
  sfree(st->host);
  sfree(st->connaddr);
  sfree(st->username);
  sfree(st->password);

  ignorelist_free(st->ignorelist);
  pthread_mutex_destroy(&st->sensor_list_lock);
  sfree(st);
}
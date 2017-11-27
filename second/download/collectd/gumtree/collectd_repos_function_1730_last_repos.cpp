static ovs_callback_t *ovs_db_callback_get(ovs_db_t *pdb, uint64_t uid) {
  for (ovs_callback_t *cb = pdb->remote_cb; cb != NULL; cb = cb->next)
    if (cb->uid == uid)
      return cb;
  return NULL;
}
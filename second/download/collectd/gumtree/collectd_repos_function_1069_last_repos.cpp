static void mcelog_update_dimm_stats(llentry_t *dimm,
                                     const mcelog_memory_rec_t *rec) {
  pthread_mutex_lock(&g_mcelog_config.dimms_lock);
  memcpy(dimm->value, rec, sizeof(mcelog_memory_rec_t));
  pthread_mutex_unlock(&g_mcelog_config.dimms_lock);
}
static llentry_t *mcelog_dimm(const mcelog_memory_rec_t *rec,
                              llist_t *dimms_list) {

  char dimm_name[DATA_MAX_NAME_LEN];

  if (strlen(rec->dimm_name) > 0) {
    snprintf(dimm_name, sizeof(dimm_name), "%s_%s", rec->location,
             rec->dimm_name);
  } else
    sstrncpy(dimm_name, rec->location, sizeof(dimm_name));

  llentry_t *dimm_le = llist_search(g_mcelog_config.dimms_list, dimm_name);

  if (dimm_le != NULL)
    return dimm_le;

  /* allocate new linked list entry */
  mcelog_memory_rec_t *dimm_mr = calloc(1, sizeof(*dimm_mr));
  if (dimm_mr == NULL) {
    ERROR(MCELOG_PLUGIN ": Error allocating dimm memory item");
    return NULL;
  }
  char *p_name = strdup(dimm_name);
  if (p_name == NULL) {
    ERROR(MCELOG_PLUGIN ": strdup: error");
    free(dimm_mr);
    return NULL;
  }

  /* add new dimm */
  dimm_le = llentry_create(p_name, dimm_mr);
  if (dimm_le == NULL) {
    ERROR(MCELOG_PLUGIN ": llentry_create(): error");
    free(dimm_mr);
    free(p_name);
    return NULL;
  }
  pthread_mutex_lock(&g_mcelog_config.dimms_lock);
  llist_append(g_mcelog_config.dimms_list, dimm_le);
  pthread_mutex_unlock(&g_mcelog_config.dimms_lock);

  return dimm_le;
}
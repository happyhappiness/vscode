static int ovs_db_result_cb(ovs_db_t *pdb, yajl_val jnode) {
  ovs_callback_t *cb = NULL;
  yajl_val jresult;
  yajl_val jerror;
  yajl_val jid;
  const char *result_path[] = {"result", NULL};
  const char *error_path[] = {"error", NULL};
  const char *id_path[] = {"id", NULL};

  jresult = yajl_tree_get(jnode, result_path, yajl_t_any);
  jerror = yajl_tree_get(jnode, error_path, yajl_t_any);
  jid = yajl_tree_get(jnode, id_path, yajl_t_string);

  /* check & get result attributes */
  if (!jresult || !jerror || !jid)
    return -1;

  /* try to find registered callback */
  pthread_mutex_lock(&pdb->mutex);
  cb = ovs_db_table_callback_get(pdb, jid);
  if (cb != NULL && cb->result.call != NULL) {
    /* call registered callback */
    cb->result.call(jresult, jerror);
    /* unlock owner of the reply */
    sem_post(&cb->result.sync);
  }

  pthread_mutex_unlock(&pdb->mutex);
  return 0;
}
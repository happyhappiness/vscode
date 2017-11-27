static void cdbi_database_free(cdbi_database_t *db) /* {{{ */
{
  if (db == NULL)
    return;

  sfree(db->name);
  sfree(db->select_db);
  sfree(db->driver);
  sfree(db->host);

  for (size_t i = 0; i < db->driver_options_num; i++) {
    sfree(db->driver_options[i].key);
    if (!db->driver_options[i].is_numeric)
      sfree(db->driver_options[i].value.string);
  }
  sfree(db->driver_options);

  if (db->q_prep_areas)
    for (size_t i = 0; i < db->queries_num; ++i)
      udb_query_delete_preparation_area(db->q_prep_areas[i]);
  sfree(db->q_prep_areas);
  /* N.B.: db->queries references objects "owned" by the global queries
   * variable. Free the array here, but not the content. */
  sfree(db->queries);

  sfree(db);
}
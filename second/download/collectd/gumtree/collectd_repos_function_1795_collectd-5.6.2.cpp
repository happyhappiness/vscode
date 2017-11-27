static void o_database_free(o_database_t *db) /* {{{ */
{
  if (db == NULL)
    return;

  sfree(db->name);
  sfree(db->connect_id);
  sfree(db->username);
  sfree(db->password);
  sfree(db->queries);

  if (db->q_prep_areas != NULL)
    for (size_t i = 0; i < db->queries_num; ++i)
      udb_query_delete_preparation_area(db->q_prep_areas[i]);
  free(db->q_prep_areas);

  sfree(db);
}
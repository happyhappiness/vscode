static void cdbi_database_free (cdbi_database_t *db) /* {{{ */
{
  size_t i;

  if (db == NULL)
    return;

  sfree (db->name);
  sfree (db->driver);

  for (i = 0; i < db->driver_options_num; i++)
  {
    sfree (db->driver_options[i].key);
    if (!db->driver_options[i].is_numeric)
      sfree (db->driver_options[i].value.string);
  }
  sfree (db->driver_options);

  if (db->q_prep_areas)
    for (i = 0; i < db->queries_num; ++i)
      udb_query_delete_preparation_area (db->q_prep_areas[i]);
  free (db->q_prep_areas);

  sfree (db);
}
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
    sfree (db->driver_options[i].value);
  }
  sfree (db->driver_options);

  sfree (db);
}
static void o_database_free (o_database_t *db) /* {{{ */
{
  if (db == NULL)
    return;

  sfree (db->name);
  sfree (db->connect_id);
  sfree (db->username);
  sfree (db->password);
  sfree (db->queries);

  sfree (db);
}
static int cx_read (user_data_t *ud) /* {{{ */
{
  cx_t *db;

  if ((ud == NULL) || (ud->data == NULL))
  {
    ERROR ("curl_xml plugin: cx_read: Invalid user data.");
    return (-1);
  }

  db = (cx_t *) ud->data;

  return cx_curl_perform (db, db->curl);
}
static _Bool check_send_okay (const value_list_t *vl) /* {{{ */
{
  _Bool received = false;
  int status;

  if (network_config_forward != 0)
    return (true);

  if (vl->meta == NULL)
    return (true);

  status = meta_data_get_boolean (vl->meta, "network:received", &received);
  if (status == -ENOENT)
    return (true);
  else if (status != 0)
  {
    ERROR ("network plugin: check_send_okay: meta_data_get_boolean failed "
	"with status %i.", status);
    return (true);
  }

  /* By default, only *send* value lists that were not *received* by the
   * network plugin. */
  return (!received);
}
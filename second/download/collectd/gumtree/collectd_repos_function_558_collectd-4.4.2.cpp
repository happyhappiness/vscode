static void domain_entity_update_handler (enum ipmi_update_e op,
    ipmi_domain_t *domain,
    ipmi_entity_t *entity,
    void *user_data)
{
  int status;

  if (op == IPMI_ADDED)
  {
    status = ipmi_entity_add_sensor_update_handler (entity,
        entity_sensor_update_handler, /* user data = */ NULL);
    if (status != 0)
    {
      c_ipmi_error ("ipmi_entity_add_sensor_update_handler", status);
    }
  }
  else if (op == IPMI_DELETED)
  {
    status = ipmi_entity_remove_sensor_update_handler (entity,
        entity_sensor_update_handler, /* user data = */ NULL);
    if (status != 0)
    {
      c_ipmi_error ("ipmi_entity_remove_sensor_update_handler", status);
    }
  }
}
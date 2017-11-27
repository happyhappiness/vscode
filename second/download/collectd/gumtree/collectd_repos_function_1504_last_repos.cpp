static void c_ipmi_add_instance(c_ipmi_instance_t *instance) {
  if (instances == NULL) {
    instances = instance;
    return;
  }

  c_ipmi_instance_t *last = instances;

  while (last->next != NULL)
    last = last->next;

  last->next = instance;
}
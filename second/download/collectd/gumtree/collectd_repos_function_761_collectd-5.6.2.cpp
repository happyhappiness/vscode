static int redis_node_add(const redis_node_t *rn) /* {{{ */
{
  redis_node_t *rn_copy;
  redis_node_t *rn_ptr;

  /* Check for duplicates first */
  for (rn_ptr = nodes_head; rn_ptr != NULL; rn_ptr = rn_ptr->next)
    if (strcmp(rn->name, rn_ptr->name) == 0)
      break;

  if (rn_ptr != NULL) {
    ERROR("redis plugin: A node with the name `%s' already exists.", rn->name);
    return (-1);
  }

  rn_copy = malloc(sizeof(*rn_copy));
  if (rn_copy == NULL) {
    ERROR("redis plugin: malloc failed adding redis_node to the tree.");
    return (-1);
  }

  memcpy(rn_copy, rn, sizeof(*rn_copy));
  rn_copy->next = NULL;

  DEBUG("redis plugin: Adding node \"%s\".", rn->name);

  if (nodes_head == NULL)
    nodes_head = rn_copy;
  else {
    rn_ptr = nodes_head;
    while (rn_ptr->next != NULL)
      rn_ptr = rn_ptr->next;
    rn_ptr->next = rn_copy;
  }

  return (0);
}
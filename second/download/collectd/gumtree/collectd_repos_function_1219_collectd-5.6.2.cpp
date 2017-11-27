static void wm_config_free(void *ptr) /* {{{ */
{
  wm_node_t *node = ptr;

  if (node == NULL)
    return;

  if (mongo_is_connected(node->conn))
    mongo_destroy(node->conn);

  sfree(node->host);
  sfree(node);
}
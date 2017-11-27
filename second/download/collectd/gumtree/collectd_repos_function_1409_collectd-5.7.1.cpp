static void wr_config_free(void *ptr) /* {{{ */
{
  wr_node_t *node = ptr;

  if (node == NULL)
    return;

  if (node->conn != NULL) {
    redisFree(node->conn);
    node->conn = NULL;
  }

  sfree(node->host);
  sfree(node);
}
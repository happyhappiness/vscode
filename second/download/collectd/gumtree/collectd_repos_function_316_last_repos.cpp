static int apcups_init(void) {
  if (conf_node == NULL)
    conf_node = APCUPS_DEFAULT_NODE;

  if (conf_service == NULL)
    conf_service = APCUPS_DEFAULT_SERVICE;

  return 0;
}
void config_init(struct OperationConfig* config)
{
  memset(config, 0, sizeof(struct OperationConfig));

  config->postfieldsize = -1;
  config->use_httpget = FALSE;
  config->create_dirs = FALSE;
  config->maxredirs = DEFAULT_MAXREDIRS;
  config->proto = CURLPROTO_ALL; /* FIXME: better to read from library */
  config->proto_present = FALSE;
  config->proto_redir = CURLPROTO_ALL & /* All except FILE, SCP and SMB */
                        ~(CURLPROTO_FILE | CURLPROTO_SCP | CURLPROTO_SMB |
                          CURLPROTO_SMBS);
  config->proto_redir_present = FALSE;
  config->proto_default = NULL;
  config->tcp_nodelay = TRUE; /* enabled by default */
}
void
XmlRpc::cleanup() {
  if (!is_valid())
    return;

  xmlrpc_registry_free((xmlrpc_registry*)m_registry);
  xmlrpc_env_clean((xmlrpc_env*)m_env);
  delete (xmlrpc_env*)m_env;
}
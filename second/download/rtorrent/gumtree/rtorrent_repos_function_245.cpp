void
XmlRpc::set_dialect(int dialect) {
  if (!is_valid())
    throw torrent::input_error("Cannot select XMLRPC dialect before it is initialized.");

  xmlrpc_env localEnv;
  xmlrpc_env_init(&localEnv);

  switch (dialect) {
  case dialect_generic:
    break;

#ifdef XMLRPC_HAVE_I8
  case dialect_i8:
    xmlrpc_registry_set_dialect(&localEnv, (xmlrpc_registry*)m_registry, xmlrpc_dialect_i8);
    break;

  case dialect_apache:
    xmlrpc_registry_set_dialect(&localEnv, (xmlrpc_registry*)m_registry, xmlrpc_dialect_apache);
    break;
#endif

  default:
    xmlrpc_env_clean(&localEnv);
    throw torrent::input_error("Unsupported XMLRPC dialect selected.");
  }

  if (localEnv.fault_occurred) {
    xmlrpc_env_clean(&localEnv);
    throw torrent::input_error("Unsupported XMLRPC dialect selected.");
  }

  xmlrpc_env_clean(&localEnv);
  m_dialect = dialect;
}
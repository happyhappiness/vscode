void
XmlRpc::initialize() {
#ifndef XMLRPC_HAVE_I8
  m_dialect = dialect_generic;
#endif
  
  m_env = new xmlrpc_env;

  xmlrpc_env_init((xmlrpc_env*)m_env);
  m_registry = xmlrpc_registry_new((xmlrpc_env*)m_env);
}
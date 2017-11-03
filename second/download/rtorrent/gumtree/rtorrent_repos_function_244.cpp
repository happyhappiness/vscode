void
XmlRpc::insert_command(const char* name, const char* parm, const char* doc, int call) {
  xmlrpc_env localEnv;
  xmlrpc_env_init(&localEnv);

  xmlrpc_value* (*callSlot)(xmlrpc_env*, xmlrpc_value*, void*);

  switch (call) {
  case call_download: callSlot = &xmlrpc_call_command_d; break;
  case call_file:     callSlot = &xmlrpc_call_command_f; break;
  case call_tracker:  callSlot = &xmlrpc_call_command_t; break;
  default:            callSlot = &xmlrpc_call_command; break;
  }

  xmlrpc_registry_add_method_w_doc(&localEnv, (xmlrpc_registry*)m_registry, NULL, name,
                                   callSlot, const_cast<char*>(name), parm, doc);

  if (localEnv.fault_occurred)
    throw torrent::internal_error("Fault occured while inserting xmlrpc call.");

  xmlrpc_env_clean(&localEnv);
}
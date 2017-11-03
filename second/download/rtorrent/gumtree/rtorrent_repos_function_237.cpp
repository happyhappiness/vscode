xmlrpc_value*
xmlrpc_call_command(xmlrpc_env* env, xmlrpc_value* args, void* voidServerInfo) {
  torrent::Object object = xmlrpc_to_object(env, args);

  if (env->fault_occurred)
    return NULL;

  try {
    return object_to_xmlrpc(env, rpc::call_command((const char*)voidServerInfo, object));

  } catch (torrent::local_error& e) {
    xmlrpc_env_set_fault(env, XMLRPC_PARSE_ERROR, e.what());
    return NULL;
  }
}
xmlrpc_value*
xmlrpc_call_command_f(xmlrpc_env* env, xmlrpc_value* args, void* voidServerInfo) {
  torrent::File*  file = NULL;
  torrent::Object object = xmlrpc_to_object_target(env, args, XmlRpc::call_file, (void**)&file);

  if (env->fault_occurred)
    return NULL;

  try {
    return object_to_xmlrpc(env, rpc::commands.call_command_f((const char*)voidServerInfo, file, object));

  } catch (torrent::local_error& e) {
    xmlrpc_env_set_fault(env, XMLRPC_PARSE_ERROR, e.what());
    return NULL;
  }
}
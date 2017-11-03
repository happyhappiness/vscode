xmlrpc_value*
xmlrpc_call_command_t(xmlrpc_env* env, xmlrpc_value* args, void* voidServerInfo) {
  torrent::Tracker* tracker = NULL;
  torrent::Object   object = xmlrpc_to_object_target(env, args, XmlRpc::call_tracker, (void**)&tracker);

  if (env->fault_occurred)
    return NULL;

  try {
    return object_to_xmlrpc(env, rpc::commands.call_command_t((const char*)voidServerInfo, tracker, object));

  } catch (torrent::local_error& e) {
    xmlrpc_env_set_fault(env, XMLRPC_PARSE_ERROR, e.what());
    return NULL;
  }
}
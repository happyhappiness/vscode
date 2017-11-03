xmlrpc_value*
xmlrpc_call_command_d(xmlrpc_env* env, xmlrpc_value* args, void* voidServerInfo) {
  core::Download* download = NULL;
  torrent::Object object = xmlrpc_to_object_target(env, args, XmlRpc::call_download, (void**)&download);

  if (env->fault_occurred)
    return NULL;

  try {
    return object_to_xmlrpc(env, rpc::call_command_d((const char*)voidServerInfo, download, object));

  } catch (torrent::local_error& e) {
    xmlrpc_env_set_fault(env, XMLRPC_PARSE_ERROR, e.what());
    return NULL;
  }
}
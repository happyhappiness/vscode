void*
xmlrpc_to_index_type(xmlrpc_env* env, xmlrpc_value* value, int callType, core::Download* download) {
  int index;

  switch (xmlrpc_value_type(value)) {
  case XMLRPC_TYPE_INT:
    xmlrpc_read_int(env, value, &index);
    break;

#ifdef XMLRPC_HAVE_I8
  case XMLRPC_TYPE_I8:
    long long v2;
    xmlrpc_read_i8(env, value, &v2);
      
    index = v2;
    break;
#endif

  case XMLRPC_TYPE_STRING:
  {
    const char* str;
    xmlrpc_read_string(env, value, &str);

    if (env->fault_occurred)
      return NULL;

    const char* end = str;
    index = ::strtol(str, (char**)&end, 0);

    ::free((void*)str);

    if (*str == '\0' || *end != '\0') {
      xmlrpc_env_set_fault(env, XMLRPC_TYPE_ERROR, "Invalid index.");
      return NULL;
    }

    break;
  }

  default:
    xmlrpc_env_set_fault(env, XMLRPC_TYPE_ERROR, "Unsupported type found.");
    return NULL;
  }

  if (env->fault_occurred)
    return NULL;
    
  void* result;

  switch (callType) {
  case XmlRpc::call_file:    result = xmlrpc.get_slot_find_file()(download, index); break;
  case XmlRpc::call_tracker: result = xmlrpc.get_slot_find_tracker()(download, index); break;
  default: result = NULL; break;
  }

  if (result == NULL)
    xmlrpc_env_set_fault(env, XMLRPC_TYPE_ERROR, "Invalid index.");
      
  return result;
}
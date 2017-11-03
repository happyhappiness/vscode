core::Download*
xmlrpc_to_download(xmlrpc_env* env, xmlrpc_value* value) {
  core::Download* download = NULL;

  switch (xmlrpc_value_type(value)) {
  case XMLRPC_TYPE_STRING:
  {
    const char* str;
    xmlrpc_read_string(env, value, &str);

    if (env->fault_occurred)
      return NULL;

    if (std::strlen(str) != 40 ||
        (download = xmlrpc.get_slot_find_download()(str)) == NULL)
      xmlrpc_env_set_fault(env, XMLRPC_TYPE_ERROR, "Could not find info-hash.");

    // Urgh, seriously?
    ::free((void*)str);
    return download;
  }

  default:
    xmlrpc_env_set_fault(env, XMLRPC_TYPE_ERROR, "Unsupported type found.");
    return NULL;
  }
}
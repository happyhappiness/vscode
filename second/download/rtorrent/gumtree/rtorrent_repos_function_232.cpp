torrent::Object
xmlrpc_to_object(xmlrpc_env* env, xmlrpc_value* value) {
  switch (xmlrpc_value_type(value)) {
  case XMLRPC_TYPE_INT:
    int v;
    xmlrpc_read_int(env, value, &v);
      
    return torrent::Object((int64_t)v);

#ifdef XMLRPC_HAVE_I8
  case XMLRPC_TYPE_I8:
    long long v2;
    xmlrpc_read_i8(env, value, &v2);
      
    return torrent::Object((int64_t)v2);
#endif

    //     case XMLRPC_TYPE_BOOL:
    //     case XMLRPC_TYPE_DOUBLE:
    //     case XMLRPC_TYPE_DATETIME:

  case XMLRPC_TYPE_STRING:
  {
    const char* valueString;
    xmlrpc_read_string(env, value, &valueString);

    if (env->fault_occurred)
      return torrent::Object();

    torrent::Object result = torrent::Object(std::string(valueString));

    // Urgh, seriously?
    ::free((void*)valueString);
    return result;
  }

    //     case XMLRPC_TYPE_BASE64:
  case XMLRPC_TYPE_ARRAY:
  {
    torrent::Object result(torrent::Object::TYPE_LIST);
    torrent::Object::list_type& listRef = result.as_list();

    unsigned int last = xmlrpc_array_size(env, value);

    if (env->fault_occurred)
      return torrent::Object();

    // Move this into a helper function.
    for (unsigned int i = 0; i != last; i++) {
      // Need to decref.
      xmlrpc_value* tmp;
      xmlrpc_array_read_item(env, value, i, &tmp);

      if (env->fault_occurred)
        return torrent::Object();

      listRef.push_back(xmlrpc_to_object(env, tmp));
      xmlrpc_DECREF(tmp);
    }

    return result;
  }

  //     case XMLRPC_TYPE_STRUCT:
    //     case XMLRPC_TYPE_C_PTR:
    //     case XMLRPC_TYPE_NIL:
    //     case XMLRPC_TYPE_DEAD:
  default:
    xmlrpc_env_set_fault(env, XMLRPC_TYPE_ERROR, "Unsupported type found.");
    return torrent::Object();
  }
}
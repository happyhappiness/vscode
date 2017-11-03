torrent::Object
xmlrpc_to_object_target(xmlrpc_env* env, xmlrpc_value* value, int callType, void** target) {
  switch (xmlrpc_value_type(value)) {
  case XMLRPC_TYPE_STRING:
    if (callType != XmlRpc::call_download) {
      xmlrpc_env_set_fault(env, XMLRPC_TYPE_ERROR, "Unsupported type found.");
      break;
    }

    *target = xmlrpc_to_download(env, value);
    break;

  case XMLRPC_TYPE_ARRAY:
  {
    unsigned int current = 0;
    unsigned int last = xmlrpc_array_size(env, value);

    if (env->fault_occurred)
      break;

    if (last < 1) {
      xmlrpc_env_set_fault(env, XMLRPC_TYPE_ERROR, "Too few arguments.");
      break;
    }

    {
      xmlrpc_value* tmp;
      xmlrpc_array_read_item(env, value, current++, &tmp);

      if (env->fault_occurred)
        break;

      *target = xmlrpc_to_download(env, tmp);
      xmlrpc_DECREF(tmp);

      if (env->fault_occurred)
        break;
    }

    if (callType == XmlRpc::call_file || callType == XmlRpc::call_tracker) {
      if (current == last) {
        xmlrpc_env_set_fault(env, XMLRPC_TYPE_ERROR, "Too few arguments.");
        break;
      }

      xmlrpc_value* tmp;
      xmlrpc_array_read_item(env, value, current++, &tmp);

      if (env->fault_occurred)
        break;

      *target = xmlrpc_to_index_type(env, tmp, callType, (core::Download*)*target);
      xmlrpc_DECREF(tmp);

      if (env->fault_occurred)
        break;
    }

    torrent::Object result;

    if (current + 1 > last) {
      result = torrent::Object(torrent::Object::TYPE_LIST);
      torrent::Object::list_type& listRef = result.as_list();

      // Move this into a helper function?
      while (current != last) {
        xmlrpc_value* tmp;
        xmlrpc_array_read_item(env, value, current++, &tmp);

        if (env->fault_occurred)
          break;

        listRef.push_back(xmlrpc_to_object(env, tmp));
        xmlrpc_DECREF(tmp);
      }

      return result;

    } else if (current + 1 == last) {
      // Need to decref.
      xmlrpc_value* tmp;
      xmlrpc_array_read_item(env, value, current, &tmp);

      if (env->fault_occurred)
        break;

      result = xmlrpc_to_object(env, tmp);
      xmlrpc_DECREF(tmp);
    }

    return result;
  }

  default:
    xmlrpc_env_set_fault(env, XMLRPC_TYPE_ERROR, "Unsupported type found.");
  }

  return torrent::Object();
}
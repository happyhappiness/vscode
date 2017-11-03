xmlrpc_value*
object_to_xmlrpc(xmlrpc_env* env, const torrent::Object& object) {
  switch (object.type()) {
  case torrent::Object::TYPE_VALUE:

#ifdef XMLRPC_HAVE_I8
    if (xmlrpc.dialect() != XmlRpc::dialect_generic)
      return xmlrpc_i8_new(env, object.as_value());
#else
    return xmlrpc_int_new(env, object.as_value());
#endif

  case torrent::Object::TYPE_STRING:
    return xmlrpc_string_new(env, object.as_string().c_str());

  case torrent::Object::TYPE_LIST:
  {
    xmlrpc_value* result = xmlrpc_array_new(env);
    
    for (torrent::Object::list_type::const_iterator itr = object.as_list().begin(), last = object.as_list().end(); itr != last; itr++)
      xmlrpc_array_append_item(env, result, object_to_xmlrpc(env, *itr));

    return result;
  }

  case torrent::Object::TYPE_MAP:
  {
    xmlrpc_value* result = xmlrpc_struct_new(env);
    
    for (torrent::Object::map_type::const_iterator itr = object.as_map().begin(), last = object.as_map().end(); itr != last; itr++)
      xmlrpc_struct_set_value(env, result, itr->first.c_str(), object_to_xmlrpc(env, itr->second));

    return result;
  }

  default:
    return xmlrpc_int_new(env, 0);
  }
}
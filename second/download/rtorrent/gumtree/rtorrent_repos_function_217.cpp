void
parse_command_execute(core::Download* download, torrent::Object* object) {
  if (object->is_list()) {
    for (torrent::Object::list_type::iterator itr = object->as_list().begin(), last = object->as_list().end(); itr != last; itr++)
      parse_command_execute(download, &*itr);

  } else if (*object->as_string().c_str() == '$') {
    const std::string& str = object->as_string();

    *object = parse_command_d_single(download, str.c_str() + 1, str.c_str() + str.size());
  }
}
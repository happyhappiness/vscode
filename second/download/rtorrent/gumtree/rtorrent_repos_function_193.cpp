CommandMap::iterator
CommandMap::insert(key_type key, Command* variable, int flags, const char* parm, const char* doc) {
  iterator itr = base_type::find(key);

  if (itr != base_type::end())
    throw torrent::internal_error("CommandMap::insert(...) tried to insert an already existing key.");

  return base_type::insert(itr, value_type(key, command_map_data_type(variable, flags, parm, doc)));
}
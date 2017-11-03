void
initialize_command_file() {
  ADD_CF_VALUE_UNI("is_created",       std::mem_fun(&torrent::File::is_created));
  ADD_CF_VALUE_UNI("is_open",          std::mem_fun(&torrent::File::is_open));

  ADD_CF_VALUE_UNI("size_bytes",       std::mem_fun(&torrent::File::size_bytes));
  ADD_CF_VALUE_UNI("size_chunks",      std::mem_fun(&torrent::File::size_chunks));
  ADD_CF_VALUE_UNI("completed_chunks", std::mem_fun(&torrent::File::completed_chunks));

  ADD_CF_VALUE_UNI("offset",           std::mem_fun(&torrent::File::offset));
  ADD_CF_VALUE_UNI("range_first",      std::mem_fun(&torrent::File::range_first));
  ADD_CF_VALUE_UNI("range_second",     std::mem_fun(&torrent::File::range_second));

  ADD_CF_VALUE_BI("priority",          std::ptr_fun(&apply_f_set_priority), std::mem_fun(&torrent::File::priority));

  ADD_CF_STRING_UNI("path",            std::ptr_fun(&apply_f_path));
  ADD_CF_STRING_UNI("path_components", std::ptr_fun(&apply_f_path_components));
  ADD_CF_STRING_UNI("path_depth",      std::ptr_fun(&apply_f_path_depth));
  ADD_CF_STRING_UNI("frozen_path",     std::mem_fun(&torrent::File::frozen_path));

  ADD_CF_VALUE_UNI("match_depth_prev", std::mem_fun(&torrent::File::match_depth_prev));
  ADD_CF_VALUE_UNI("match_depth_next", std::mem_fun(&torrent::File::match_depth_next));

  ADD_CF_VALUE_UNI("last_touched",     std::mem_fun(&torrent::File::last_touched));
}
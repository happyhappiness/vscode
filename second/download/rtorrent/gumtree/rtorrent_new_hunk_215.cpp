    target = rpc::call_command_d_string("get_d_base_path", download);

  } else {
    throw torrent::input_error("Unknown type argument.");
  }

  switch (changeType) {
  case 0:
    if (symlink(target.c_str(), link.c_str()) == -1)
      //     control->core()->push_log("create_link failed: " + std::string(rak::error_number::current().c_str()));
      //     control->core()->push_log("create_link failed: " + std::string(rak::error_number::current().c_str()) + " to " + target);
      ; // Disabled.
    break;

  case 1:
  {
    rak::file_stat fileStat;
    rak::error_number::clear_global();

    if (!fileStat.update_link(link) || !fileStat.is_link() ||
        unlink(link.c_str()) == -1)
      ; //     control->core()->push_log("delete_link failed: " + std::string(rak::error_number::current().c_str()));

    break;
  }
  default:
    break;
  }

  return torrent::Object();
}

void
apply_d_delete_tied(core::Download* download) {
  const std::string& tie = rpc::call_command_d_string("get_d_tied_to_file", download);

  if (tie.empty())
    return;

  if (::unlink(rak::path_expand(tie).c_str()) == -1)
    control->core()->push_log_std("Could not unlink tied file: " + std::string(rak::error_number::current().c_str()));

  rpc::call_command_d("set_d_tied_to_file", download, std::string());
}

void
apply_d_connection_type(core::Download* download, const std::string& name) {
  torrent::Download::ConnectionType connType;

  if (name == "leech")
    connType = torrent::Download::CONNECTION_LEECH;
  else if (name == "seed")
    connType = torrent::Download::CONNECTION_SEED;
  else
    throw torrent::input_error("Unknown peer connection type selected.");

  download->download()->set_connection_type(connType);
}

const char*
retrieve_d_connection_type(core::Download* download) {
  switch (download->download()->connection_type()) {
  case torrent::Download::CONNECTION_LEECH:
    return "leech";
  case torrent::Download::CONNECTION_SEED:
    return "seed";
  default:
    return "unknown";
  }
}

const char*
retrieve_d_priority_str(core::Download* download) {
  switch (download->priority()) {
  case 0:
    return "off";
  case 1:
    return "low";
  case 2:
    return "normal";
  case 3:
    return "high";
  default:
    throw torrent::input_error("Priority out of range.");
  }
}

torrent::Object
apply_d_ratio(core::Download* download) {
  int64_t bytesDone = download->download()->bytes_done();
  int64_t upTotal   = download->download()->up_rate()->total();

  return bytesDone > 0 ? (1000 * upTotal) / bytesDone : 0;
}

#define ADD_CD_SLOT(key, function, slot, parm, doc)    \
  commandDownloadSlotsItr->set_slot(slot); \
  rpc::commands.insert_download(key, commandDownloadSlotsItr++, &rpc::CommandDownloadSlot::function, rpc::CommandMap::flag_dont_delete, parm, doc);

#define ADD_CD_SLOT_PUBLIC(key, function, slot, parm, doc)    \
  commandDownloadSlotsItr->set_slot(slot); \
  rpc::commands.insert_download(key, commandDownloadSlotsItr++, &rpc::CommandDownloadSlot::function, rpc::CommandMap::flag_dont_delete | rpc::CommandMap::flag_public_xmlrpc, parm, doc);

#define ADD_CD_VOID(key, slot) \
  ADD_CD_SLOT_PUBLIC("get_d_" key, call_unknown, rpc::object_d_fn(slot), "i:", "")

#define ADD_CD_V_VOID(key, slot) \
  ADD_CD_SLOT_PUBLIC("d_" key, call_unknown, rpc::object_d_fn(slot), "i:", "")

#define ADD_CD_F_VOID(key, slot) \
  ADD_CD_SLOT_PUBLIC("d_" key, call_unknown, rpc::object_void_d_fn(slot), "i:", "")

#define ADD_CD_LIST(key, slot) \
  ADD_CD_SLOT_PUBLIC(key, call_list, slot, "i:", "")

#define ADD_CD_VARIABLE_VALUE(key, firstKey, secondKey) \
  ADD_CD_SLOT_PUBLIC("get_d_" key, call_unknown, rpc::get_variable_d_fn(firstKey, secondKey), "i:", ""); \
  ADD_CD_SLOT("set_d_" key, call_value,   rpc::set_variable_d_fn(firstKey, secondKey), "i:i", "");

#define ADD_CD_VARIABLE_VALUE_PUBLIC(key, firstKey, secondKey) \
  ADD_CD_SLOT_PUBLIC("get_d_" key, call_unknown, rpc::get_variable_d_fn(firstKey, secondKey), "i:", ""); \
  ADD_CD_SLOT_PUBLIC("set_d_" key, call_value,   rpc::set_variable_d_fn(firstKey, secondKey), "i:i", "");

#define ADD_CD_VARIABLE_STRING(key, firstKey, secondKey) \
  ADD_CD_SLOT_PUBLIC("get_d_" key, call_unknown, rpc::get_variable_d_fn(firstKey, secondKey), "i:", ""); \
  ADD_CD_SLOT("set_d_" key, call_string,  rpc::set_variable_d_fn(firstKey, secondKey), "i:s", "");

#define ADD_CD_VALUE_UNI(key, get) \
  ADD_CD_SLOT_PUBLIC("get_d_" key, call_unknown, rpc::object_void_d_fn(get), "i:", "")

#define ADD_CD_VALUE_BI(key, set, get) \
  ADD_CD_SLOT_PUBLIC("set_d_" key, call_value, rpc::object_value_d_fn(set), "i:i", "") \
  ADD_CD_SLOT_PUBLIC("get_d_" key, call_unknown, rpc::object_void_d_fn(get), "i:", "")

#define ADD_CD_VALUE_MEM_BI(key, target, set, get) \
  ADD_CD_VALUE_BI(key, rak::on2(std::mem_fun(target), std::mem_fun(set)), rak::on(std::mem_fun(target), std::mem_fun(get)));

#define ADD_CD_VALUE_MEM_UNI(key, target, get) \
  ADD_CD_SLOT_PUBLIC("get_d_" key, call_unknown, rpc::object_void_d_fn(rak::on(rak::on(std::mem_fun(&core::Download::download), std::mem_fun(target)), std::mem_fun(get))), "i:", "");

#define ADD_CD_STRING_UNI(key, get) \
  ADD_CD_SLOT_PUBLIC("get_d_" key, call_unknown, rpc::object_void_d_fn(get), "s:", "")

#define ADD_CD_STRING_BI(key, set, get) \
  ADD_CD_SLOT_PUBLIC("set_d_" key, call_string, rpc::object_string_d_fn(set), "i:s", "") \
  ADD_CD_SLOT_PUBLIC("get_d_" key, call_unknown, rpc::object_void_d_fn(get), "s:", "")

void
add_copy_to_download(const char* src, const char* dest) {
  rpc::CommandMap::iterator itr = rpc::commands.find(src);

  if (itr == rpc::commands.end())

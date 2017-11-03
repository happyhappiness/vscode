inline ElementBase*
Download::create_info() {
  using namespace display::helpers;

  ElementText* element = new ElementText(m_download);

  element->set_column(1);
  element->set_interval(1);

  // Get these bindings with some kind of string map.

  element->push_column("Name:",             te_string(&torrent::Download::name));
  element->push_column("Local id:",         te_string(&torrent::Download::local_id, string_base::flag_escape_html));
  element->push_column("Info hash:",        te_string(&torrent::Download::info_hash, string_base::flag_escape_hex));
  element->push_column("Created:",          te_value(&torrent::Download::creation_date, value_base::flag_date), " ", te_value(&torrent::Download::creation_date, value_base::flag_time));

  element->push_back("");
  element->push_column("Directory:",        te_string(&torrent::FileList::root_dir));
  element->push_column("Tied to file:",     te_variable_string("d.get_tied_to_file"));
  element->push_column("File stats:",
                       te_branch(&core::Download::c_file_list, &torrent::FileList::is_multi_file, te_string("multi"), te_string("single")),
                       " ", te_value(&torrent::FileList::size_files), " files");

  element->push_back("");
  element->push_column("Chunks:",           te_value(&torrent::FileList::completed_chunks), " / ", te_value(&torrent::FileList::size_chunks), " * ", te_value(&torrent::FileList::chunk_size));
  element->push_column("Priority:",         te_variable_value("d.get_priority"));

  element->push_column("State changed:",    te_variable_value("d.get_state_changed", value_base::flag_timer | value_base::flag_elapsed));

  element->push_back("");
  element->push_column("Memory usage:",     te_value(&torrent::ChunkManager::memory_usage, value_base::flag_mb), " MB");
  element->push_column("Max memory usage:", te_value(&torrent::ChunkManager::max_memory_usage, value_base::flag_mb), " MB");
  element->push_column("Free diskspace:",   te_value(&torrent::FileList::free_diskspace, value_base::flag_mb), " MB");
  element->push_column("Safe diskspace:",   te_value(&torrent::ChunkManager::safe_free_diskspace, value_base::flag_mb), " MB");

  element->push_back("");
  element->push_column("Connection type:",  te_variable_string("d.get_connection_current"));
  element->push_column("Safe sync:",        te_branch(&torrent::ChunkManager::safe_sync, torrent::chunk_manager(), te_string("yes"), te_string("no")));
  element->push_column("Send buffer:",      te_value(&torrent::ConnectionManager::send_buffer_size, value_base::flag_kb), " KB");
  element->push_column("Receive buffer:",   te_value(&torrent::ConnectionManager::receive_buffer_size, value_base::flag_kb), " KB");

  element->push_back("");
  element->push_column("Upload:",           te_variable_value("d.get_up_rate", value_base::flag_kb), " KB / ", te_variable_value("d.get_up_total", value_base::flag_xb));
  element->push_column("Download:",         te_variable_value("d.get_down_rate", value_base::flag_kb), " KB / ", te_variable_value("d.get_down_total", value_base::flag_xb));
  element->push_column("Skipped:",          te_variable_value("d.get_skip_rate", value_base::flag_kb), " KB / ", te_variable_value("d.get_skip_total", value_base::flag_xb));
  element->push_column("Preload:",          te_value(&torrent::ChunkManager::preload_type), " / ", te_value(&torrent::ChunkManager::stats_preloaded), " / ", te_value(&torrent::ChunkManager::stats_not_preloaded));

  element->set_column_width(element->column_width() + 1);

  return element;
}
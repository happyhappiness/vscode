void
add_copy_to_download(const char* src, const char* dest) {
  rpc::CommandMap::iterator itr = rpc::commands.find(src);

  if (itr == rpc::commands.end())
    throw torrent::internal_error("add_copy_to_download(...) key not found.");

  rpc::commands.insert(dest, itr->second);
}
torrent::Object
apply_f_path_depth(torrent::File* file) {
  return (int64_t)file->path()->size();
}
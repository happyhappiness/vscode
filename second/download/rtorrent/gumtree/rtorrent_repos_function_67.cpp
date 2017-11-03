void
apply_f_set_priority(torrent::File* file, uint32_t value) {
  if (value > torrent::PRIORITY_HIGH)
    throw torrent::input_error("Invalid value.");

  file->set_priority((torrent::priority_t)value);
}
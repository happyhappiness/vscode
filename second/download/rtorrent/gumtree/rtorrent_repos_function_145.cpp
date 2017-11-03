std::string
retrieve_d_base_filename(core::Download* download) {
  const std::string* base;

  if (download->file_list()->is_multi_file())
    base = &download->file_list()->root_dir();
  else
    base = &download->file_list()->at(0)->frozen_path();

  std::string::size_type split = base->rfind('/');

  if (split == std::string::npos)
    return *base;
  else
    return base->substr(split + 1);
}
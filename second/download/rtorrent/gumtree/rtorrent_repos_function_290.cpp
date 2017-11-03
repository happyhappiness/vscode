const char*
element_file_list_filename(const torrent::FileListIterator* itr) {
  if ((**itr)->path()->empty())
    return "EMPTY";

  if (itr->depth() >= (**itr)->path()->size())
    return "ERROR";

  return (**itr)->path()->at(itr->depth()).c_str();
}
inline ElementText*
element_file_list_create_info() {
  using namespace display::helpers;

  ElementText* element = new ElementText(NULL);

  element->set_column(1);
  element->set_interval(1);

  element->push_back("File info:");
  element->push_back("");
  
  element->push_column("Filename:", te_string(&element_file_list_filename));
  element->push_back("");
  
  element->push_column("Size:",   te_branch(&torrent::FileListIterator::is_file, te_value(&torrent::File::size_bytes, value_base::flag_xb), te_string("---")));
  element->push_column("Chunks:", te_value(&torrent::File::completed_chunks), " / ", te_value(&torrent::File::size_chunks));
  element->push_column("Range:",  te_value(&torrent::File::range_first), " - ", te_value(&torrent::File::range_second));

  element->set_column_width(element->column_width() + 1);

  return element;
}
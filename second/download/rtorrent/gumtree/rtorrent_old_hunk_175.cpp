
  fstr << "url: " << url << std::endl << "---" << std::endl;
  fstr.write(data, size);
  fstr << std::endl <<"---" << std::endl;
}

// Hmm... find some better place for all this.
void
Manager::delete_tied(Download* d) {
  const std::string& tie = d->variable()->get_string("tied_to_file");

  // This should be configurable, need to wait for the variable

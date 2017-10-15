  fstr << "url: " << url << std::endl << "---" << std::endl;
  fstr.write(data, size);
  fstr << std::endl <<"---" << std::endl;
}

// Hmm... find some better place for all this.
void
Manager::delete_tied(Download* d) {
  const std::string& tie = d->variable()->get_string("tied_to_file");

  // This should be configurable, need to wait for the variable
  // thingie to be implemented.
  if (tie.empty())
    return;

  if (::unlink(rak::path_expand(tie).c_str()) == -1)
    push_log("Could not unlink tied file: " + std::string(rak::error_number::current().c_str()));

  d->variable()->set("tied_to_file", std::string());
}

Manager::Manager() :
  m_hashingView(NULL),

  m_pollManager(NULL),

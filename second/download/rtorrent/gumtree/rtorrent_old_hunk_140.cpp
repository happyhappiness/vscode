  fstr << "url: " << url << std::endl << "---" << std::endl;
  fstr.write(data, size);
  fstr << std::endl <<"---" << std::endl;
}

// Hmm... find some better place for all this.
static void
delete_tied(Download* d) {
  const std::string tie = d->variable()->get("tied_to_file").as_string();

  // This should be configurable, need to wait for the variable
  // thingie to be implemented.
  if (!tie.empty())
    ::unlink(tie.c_str());
}

Manager::Manager() :
  m_hashingView(NULL),

  m_pollManager(NULL),

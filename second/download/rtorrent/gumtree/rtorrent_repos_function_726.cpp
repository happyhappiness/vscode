void operator () (std::string& filename) {
    rak::file_stat fs;

    if (!fs.update(rak::path_expand(m_base + filename)))
      return;

    else if (fs.is_directory())
      filename += '/';
  }
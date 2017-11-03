Download*
DownloadList::create(std::istream* str, bool printLog) {
  torrent::Object* object = new torrent::Object;
  torrent::Download download;

  try {
    *str >> *object;
    
    // Don't throw input_error from here as gcc-3.3.5 produces bad
    // code.
    if (str->fail()) {
      delete object;

      if (printLog)
        control->core()->push_log("Could not create download, the input is not a valid torrent.");

      return NULL;
    }

    download = torrent::download_add(object);

  } catch (torrent::local_error& e) {
    delete object;

    if (printLog)
      control->core()->push_log(e.what());

    return NULL;
  }

  // There's no non-critical exceptions that should be throwable by
  // the ctor, so don't catch.
  return new Download(download);
}
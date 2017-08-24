{
    std::string new_destination = destination;
    SystemTools::ConvertToUnixSlashes(new_destination);
    new_destination += '/';
    std::string source_name = source;
    new_destination += SystemTools::GetFilenameName(source_name);
    if (SystemTools::FilesDiffer(source, new_destination)) {
      return SystemTools::CopyFileAlways(source, destination);
    } else {
      // the files are the same so the copy is done return
      // true
      return true;
    }
  }
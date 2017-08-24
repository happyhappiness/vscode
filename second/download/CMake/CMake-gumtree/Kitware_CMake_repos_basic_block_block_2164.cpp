{
    const int bufferSize = 4096;
    char buffer[bufferSize];

    // If destination is a directory, try to create a file with the same
    // name as the source in that directory.

    std::string destination_dir;
    if (SystemTools::FileIsDirectory(destination)) {
      destination_dir = real_destination;
      SystemTools::ConvertToUnixSlashes(real_destination);
      real_destination += '/';
      std::string source_name = source;
      real_destination += SystemTools::GetFilenameName(source_name);
    } else {
      destination_dir = SystemTools::GetFilenamePath(destination);
    }

    // Create destination directory

    SystemTools::MakeDirectory(destination_dir);

// Open files
#if defined(_WIN32)
    kwsys::ifstream fin(
      Encoding::ToNarrow(Encoding::ToWindowsExtendedPath(source)).c_str(),
      std::ios::in | std::ios::binary);
#else
    kwsys::ifstream fin(source.c_str(), std::ios::in | std::ios::binary);
#endif
    if (!fin) {
      return false;
    }

    // try and remove the destination file so that read only destination files
    // can be written to.
    // If the remove fails continue so that files in read only directories
    // that do not allow file removal can be modified.
    SystemTools::RemoveFile(real_destination);

#if defined(_WIN32)
    kwsys::ofstream fout(
      Encoding::ToNarrow(Encoding::ToWindowsExtendedPath(real_destination))
        .c_str(),
      std::ios::out | std::ios::trunc | std::ios::binary);
#else
    kwsys::ofstream fout(real_destination.c_str(),
                         std::ios::out | std::ios::trunc | std::ios::binary);
#endif
    if (!fout) {
      return false;
    }

    // This copy loop is very sensitive on certain platforms with
    // slightly broken stream libraries (like HPUX).  Normally, it is
    // incorrect to not check the error condition on the fin.read()
    // before using the data, but the fin.gcount() will be zero if an
    // error occurred.  Therefore, the loop should be safe everywhere.
    while (fin) {
      fin.read(buffer, bufferSize);
      if (fin.gcount()) {
        fout.write(buffer, fin.gcount());
      } else {
        break;
      }
    }

    // Make sure the operating system has finished writing the file
    // before closing it.  This will ensure the file is finished before
    // the check below.
    fout.flush();

    fin.close();
    fout.close();

    if (!fout) {
      return false;
    }
  }
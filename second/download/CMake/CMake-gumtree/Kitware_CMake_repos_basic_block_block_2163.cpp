{
      destination_dir = real_destination;
      SystemTools::ConvertToUnixSlashes(real_destination);
      real_destination += '/';
      std::string source_name = source;
      real_destination += SystemTools::GetFilenameName(source_name);
    }
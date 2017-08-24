(size_t index = 0; index < cachename.size(); index++) {
    std::string cacheSize =
      this->ExtractValueFromCpuInfoFile(buffer, cachename[index]);
    if (!cacheSize.empty()) {
      pos = cacheSize.find(" KB");
      if (pos != std::string::npos) {
        cacheSize = cacheSize.substr(0, pos);
      }
      this->Features.L1CacheSize += atoi(cacheSize.c_str());
    }
  }
(std::vector<String>::iterator vit1 = finalPath.begin();
       vit1 != finalPath.end(); ++vit1) {
    if (!relativePath.empty() && *relativePath.rbegin() != '/') {
      relativePath += "/";
    }
    relativePath += *vit1;
  }
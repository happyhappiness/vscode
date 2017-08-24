{
  this->Clear();

  DIR* dir = opendir(name.c_str());

  if (!dir) {
    return 0;
  }

  for (kwsys_dirent* d = readdir(dir); d; d = readdir(dir)) {
    this->Internal->Files.push_back(d->d_name);
  }
  this->Internal->Path = name;
  closedir(dir);
  return 1;
}
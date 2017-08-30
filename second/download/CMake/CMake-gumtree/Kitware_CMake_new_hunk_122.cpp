
bool bindexplib::AddDefinitionFile(const char* filename)
{
  cmsys::ifstream infile(filename);
  if (!infile) {
    fprintf(stderr, "Couldn't open definition file '%s'\n", filename);
    return false;
  }
  std::string str;
  while (std::getline(infile, str)) {
    // skip the LIBRAY and EXPORTS lines (if any)
    if ((str.compare(0, 7, "LIBRARY") == 0) ||
        (str.compare(0, 7, "EXPORTS") == 0)) {
      continue;
    }
    // remove leading tabs & spaces
    str.erase(0, str.find_first_not_of(" \t"));
    std::size_t found = str.find(" \t DATA");
    if (found != std::string::npos) {
      str.erase(found, std::string::npos);
      this->DataSymbols.insert(str);
    } else {
      this->Symbols.insert(str);
    }
  }
  infile.close();
  return true;
}

void bindexplib::WriteFile(FILE* file)
{
  fprintf(file, "EXPORTS \n");
  for (std::set<std::string>::const_iterator i = this->DataSymbols.begin();
       i != this->DataSymbols.end(); ++i) {
    fprintf(file, "\t%s \t DATA\n", i->c_str());
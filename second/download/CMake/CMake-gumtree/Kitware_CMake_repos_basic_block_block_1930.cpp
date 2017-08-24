{
#if defined(__QNX__)
  std::string buffer;
  std::vector<const char*> args;
  args.clear();

  args.push_back("showmem");
  args.push_back("-S");
  args.push_back(0);
  buffer = this->RunProcess(args);
  args.clear();

  size_t pos = buffer.find("System RAM:");
  if (pos == std::string::npos)
    return false;
  pos = buffer.find(":", pos);
  size_t pos2 = buffer.find("M (", pos);
  if (pos2 == std::string::npos)
    return false;

  pos++;
  while (buffer[pos] == ' ')
    pos++;

  this->TotalPhysicalMemory = atoi(buffer.substr(pos, pos2 - pos).c_str());
  return true;
#endif
  return false;
}
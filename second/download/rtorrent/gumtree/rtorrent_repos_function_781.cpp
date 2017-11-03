std::string
Lockfile::locked_by_as_string() const {
  process_type p = locked_by();

  if (p.first.empty())
    return "<error>";

  std::stringstream str;
  str << p.first << ":+" << p.second;

  return str.str();
}
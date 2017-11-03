PathInput::Range
PathInput::find_incomplete(utils::Directory& d, const std::string& f) {
  Range r;

  r.first  = std::find_if(d.begin(), d.end(), std::bind2nd(rak::compare_base<std::string>(), f));
  r.second = std::find_if(r.first, d.end(), std::not1(std::bind2nd(rak::compare_base<std::string>(), f)));

  return r;
}
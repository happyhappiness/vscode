{
    std::string ret = fn.substr(0, slash_pos);
    if (ret.size() == 2 && ret[1] == ':') {
      return ret + '/';
    }
    if (ret.empty()) {
      return "/";
    }
    return ret;
  }
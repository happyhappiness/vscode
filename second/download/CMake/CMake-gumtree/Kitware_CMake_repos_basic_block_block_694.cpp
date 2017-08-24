{
  if (r.empty()) {
    return std::string();
  }
  std::ostringstream os;
  typedef typename Range::value_type ValueType;
  typedef typename Range::const_iterator InputIt;
  const InputIt first = r.begin();
  InputIt last = r.end();
  --last;
  std::copy(first, last, std::ostream_iterator<ValueType>(os, delimiter));

  os << *last;

  return os.str();
}
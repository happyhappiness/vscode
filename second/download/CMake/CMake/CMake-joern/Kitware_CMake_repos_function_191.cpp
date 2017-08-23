std::istream& operator>>(std::istream& sin, Value& root) {
  Json::Reader reader;
  bool ok = reader.parse(sin, root, true);
  if (!ok) {
    fprintf(stderr,
            "Error from reader: %s",
            reader.getFormattedErrorMessages().c_str());

    JSON_FAIL_MESSAGE("reader error");
  }
  return sin;
}
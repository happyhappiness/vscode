{
  std::string decoded;
  if (!decodeString(token, decoded))
    return false;
  currentValue() = decoded;
  currentValue().setOffsetStart(token.start_ - begin_);
  currentValue().setOffsetLimit(token.end_ - begin_);
  return true;
}
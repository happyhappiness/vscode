{
  JSON_ASSERT_MESSAGE(
      type_ == nullValue || type_ == objectValue,
      "in Json::Value::getMemberNames(), value must be objectValue");
  if (type_ == nullValue)
    return Value::Members();
  Members members;
  members.reserve(value_.map_->size());
#ifndef JSON_VALUE_USE_INTERNAL_MAP
  ObjectValues::const_iterator it = value_.map_->begin();
  ObjectValues::const_iterator itEnd = value_.map_->end();
  for (; it != itEnd; ++it)
    members.push_back(std::string((*it).first.c_str()));
#else
  ValueInternalMap::IteratorState it;
  ValueInternalMap::IteratorState itEnd;
  value_.map_->makeBeginIterator(it);
  value_.map_->makeEndIterator(itEnd);
  for (; !ValueInternalMap::equals(it, itEnd); ValueInternalMap::increment(it))
    members.push_back(std::string(ValueInternalMap::key(it)));
#endif
  return members;
}
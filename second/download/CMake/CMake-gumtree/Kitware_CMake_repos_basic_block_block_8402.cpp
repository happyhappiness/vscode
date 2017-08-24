{
  JSON_ASSERT_MESSAGE(type_ == nullValue || type_ == objectValue,
                      "in Json::Value::removeMember(): requires objectValue");
  if (type_ == nullValue)
    return null;
#ifndef JSON_VALUE_USE_INTERNAL_MAP
  CZString actualKey(key, CZString::noDuplication);
  ObjectValues::iterator it = value_.map_->find(actualKey);
  if (it == value_.map_->end())
    return null;
  Value old(it->second);
  value_.map_->erase(it);
  return old;
#else
  Value* value = value_.map_->find(key);
  if (value) {
    Value old(*value);
    value_.map_.remove(key);
    return old;
  } else {
    return null;
  }
#endif
}
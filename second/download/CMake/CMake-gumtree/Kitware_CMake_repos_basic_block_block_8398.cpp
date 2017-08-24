{
  JSON_ASSERT_MESSAGE(
      type_ == nullValue || type_ == objectValue,
      "in Json::Value::resolveReference(): requires objectValue");
  if (type_ == nullValue)
    *this = Value(objectValue);
#ifndef JSON_VALUE_USE_INTERNAL_MAP
  CZString actualKey(
      key, isStatic ? CZString::noDuplication : CZString::duplicateOnCopy);
  ObjectValues::iterator it = value_.map_->lower_bound(actualKey);
  if (it != value_.map_->end() && (*it).first == actualKey)
    return (*it).second;

  ObjectValues::value_type defaultValue(actualKey, null);
  it = value_.map_->insert(it, defaultValue);
  Value& value = (*it).second;
  return value;
#else
  return value_.map_->resolveReference(key, isStatic);
#endif
}
{
  switch (type_) {
  case nullValue:
  case intValue:
  case uintValue:
  case realValue:
  case booleanValue:
  case stringValue:
    return 0;
#ifndef JSON_VALUE_USE_INTERNAL_MAP
  case arrayValue: // size of the array is highest index + 1
    if (!value_.map_->empty()) {
      ObjectValues::const_iterator itLast = value_.map_->end();
      --itLast;
      return (*itLast).first.index() + 1;
    }
    return 0;
  case objectValue:
    return ArrayIndex(value_.map_->size());
#else
  case arrayValue:
    return Int(value_.array_->size());
  case objectValue:
    return Int(value_.map_->size());
#endif
  }
  JSON_ASSERT_UNREACHABLE;
  return 0; // unreachable;
}
{
  case nullValue:
    return false;
  case intValue:
    return value_.int_ < other.value_.int_;
  case uintValue:
    return value_.uint_ < other.value_.uint_;
  case realValue:
    return value_.real_ < other.value_.real_;
  case booleanValue:
    return value_.bool_ < other.value_.bool_;
  case stringValue:
    return (value_.string_ == 0 && other.value_.string_) ||
           (other.value_.string_ && value_.string_ &&
            strcmp(value_.string_, other.value_.string_) < 0);
#ifndef JSON_VALUE_USE_INTERNAL_MAP
  case arrayValue:
  case objectValue: {
    int delta = int(value_.map_->size() - other.value_.map_->size());
    if (delta)
      return delta < 0;
    return (*value_.map_) < (*other.value_.map_);
  }
#else
  case arrayValue:
    return value_.array_->compare(*(other.value_.array_)) < 0;
  case objectValue:
    return value_.map_->compare(*(other.value_.map_)) < 0;
#endif
  default:
    JSON_ASSERT_UNREACHABLE;
  }
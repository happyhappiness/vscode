{
  case nullValue:
    break;
  case intValue:
  case uintValue:
    value_.int_ = 0;
    break;
  case realValue:
    value_.real_ = 0.0;
    break;
  case stringValue:
    value_.string_ = 0;
    break;
#ifndef JSON_VALUE_USE_INTERNAL_MAP
  case arrayValue:
  case objectValue:
    value_.map_ = new ObjectValues();
    break;
#else
  case arrayValue:
    value_.array_ = arrayAllocator()->newArray();
    break;
  case objectValue:
    value_.map_ = mapAllocator()->newMap();
    break;
#endif
  case booleanValue:
    value_.bool_ = false;
    break;
  default:
    JSON_ASSERT_UNREACHABLE;
  }
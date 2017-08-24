{
#ifdef JSON_VALUE_USE_INTERNAL_MAP
  case arrayValue:
    if (value_.array_) {
      ValueInternalArray::IteratorState it;
      value_.array_->makeBeginIterator(it);
      return const_iterator(it);
    }
    break;
  case objectValue:
    if (value_.map_) {
      ValueInternalMap::IteratorState it;
      value_.map_->makeBeginIterator(it);
      return const_iterator(it);
    }
    break;
#else
  case arrayValue:
  case objectValue:
    if (value_.map_)
      return const_iterator(value_.map_->begin());
    break;
#endif
  default:
    break;
  }
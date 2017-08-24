(value_.map_) {
      ValueInternalMap::IteratorState it;
      value_.map_->makeEndIterator(it);
      return iterator(it);
    }
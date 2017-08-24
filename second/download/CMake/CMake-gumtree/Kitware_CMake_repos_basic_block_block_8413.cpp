{
      ValueInternalMap::IteratorState it;
      value_.map_->makeBeginIterator(it);
      return iterator(it);
    }
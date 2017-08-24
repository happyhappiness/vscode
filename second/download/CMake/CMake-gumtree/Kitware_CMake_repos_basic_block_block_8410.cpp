{
      ValueInternalMap::IteratorState it;
      value_.map_->makeBeginIterator(it);
      return const_iterator(it);
    }
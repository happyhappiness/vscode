{
      ValueInternalArray::IteratorState it;
      value_.array_->makeBeginIterator(it);
      return iterator(it);
    }
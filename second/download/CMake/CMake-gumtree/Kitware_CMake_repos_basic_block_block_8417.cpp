{
      ValueInternalArray::IteratorState it;
      value_.array_->makeEndIterator(it);
      return iterator(it);
    }
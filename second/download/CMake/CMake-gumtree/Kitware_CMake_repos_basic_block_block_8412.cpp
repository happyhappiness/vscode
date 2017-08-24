{
      ValueInternalArray::IteratorState it;
      value_.array_->makeEndIterator(it);
      return const_iterator(it);
    }
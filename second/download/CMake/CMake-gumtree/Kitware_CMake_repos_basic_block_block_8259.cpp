{
    if (freeHead_) // returns node from free list.
    {
      AllocatedType* object = freeHead_;
      freeHead_ = *(AllocatedType**)object;
      return object;
    }
    if (currentBatch_->used_ == currentBatch_->end_) {
      currentBatch_ = currentBatch_->next_;
      while (currentBatch_ && currentBatch_->used_ == currentBatch_->end_)
        currentBatch_ = currentBatch_->next_;

      if (!currentBatch_) // no free batch found, allocate a new one
      {
        currentBatch_ = allocateBatch(objectsPerPage_);
        currentBatch_->next_ = batches_; // insert at the head of the list
        batches_ = currentBatch_;
      }
    }
    AllocatedType* allocated = currentBatch_->used_;
    currentBatch_->used_ += objectPerAllocation;
    return allocated;
  }
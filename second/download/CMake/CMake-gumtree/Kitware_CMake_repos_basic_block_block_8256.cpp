{
        currentBatch_ = allocateBatch(objectsPerPage_);
        currentBatch_->next_ = batches_; // insert at the head of the list
        batches_ = currentBatch_;
      }
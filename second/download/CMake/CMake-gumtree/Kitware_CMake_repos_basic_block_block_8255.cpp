{
      BatchInfo* nextBatch = batch->next_;
      free(batch);
      batch = nextBatch;
    }
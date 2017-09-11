                                size_t slice_begin,
                                size_t slice_end,
                                size_t size_prev_slice) {
  // read from next link and send to prev one 
  LinkRecord &prev = *ring_prev, &next = *ring_next;
  // need to reply on special rank structure
  utils::Assert(next.rank == (rank + 1) % world_size &&
                rank == (prev.rank + 1) % world_size,
                "need to assume rank structure");
  // send recv buffer
  char *sendrecvbuf = reinterpret_cast<char*>(sendrecvbuf_);
  const size_t stop_read = total_size + slice_begin; 
  const size_t stop_write = total_size + slice_begin - size_prev_slice; 
  size_t write_ptr = slice_begin;
  size_t read_ptr = slice_end;
  
  while (true) {
    // select helper
    bool finished = true;

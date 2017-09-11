AllreduceBase::ReturnType
AllreduceBase::TryAllgatherRing(void *sendrecvbuf_, size_t total_size,
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
    utils::SelectHelper selecter;
    if (read_ptr != stop_read) {
      selecter.WatchRead(next.sock);
      finished = false;
    }
    if (write_ptr != stop_write) {
      if (write_ptr < read_ptr) {
        selecter.WatchWrite(prev.sock);
      }
      finished  = false;
    }
    if (finished) break;
    selecter.Select();
    if (read_ptr != stop_read && selecter.CheckRead(next.sock)) {
      size_t size = stop_read - read_ptr;
      size_t start = read_ptr % total_size;
      if (start + size > total_size) {
        size = total_size - start;
      }
      ssize_t len = next.sock.Recv(sendrecvbuf + start, size);
      if (len != -1) {
        read_ptr += static_cast<size_t>(len);
      } else {
        ReturnType ret = Errno2Return(errno);
        if (ret != kSuccess) return ReportError(&next, ret);
      }
    }
    if (write_ptr < read_ptr && write_ptr != stop_write) {
      size_t size = std::min(read_ptr, stop_write) - write_ptr;
      size_t start = write_ptr % total_size;
      if (start + size > total_size) {
        size = total_size - start;
      }
      ssize_t len = prev.sock.Send(sendrecvbuf + start, size);
      if (len != -1) {
        write_ptr += static_cast<size_t>(len);
      } else {
        ReturnType ret = Errno2Return(errno);
        if (ret != kSuccess) return ReportError(&prev, ret);
      }
    }
  }
  return kSuccess;
}
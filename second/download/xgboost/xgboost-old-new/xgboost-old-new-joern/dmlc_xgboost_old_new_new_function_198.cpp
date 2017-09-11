AllreduceBase::ReturnType
AllreduceBase::TryReduceScatterRing(void *sendrecvbuf_,
                                    size_t type_nbytes,
                                    size_t count,
                                    ReduceFunction reducer) {
  // read from next link and send to prev one 
  LinkRecord &prev = *ring_prev, &next = *ring_next;
  // need to reply on special rank structure
  utils::Assert(next.rank == (rank + 1) % world_size &&
                rank == (prev.rank + 1) % world_size,
                "need to assume rank structure");
  // total size of message
  const size_t total_size = type_nbytes * count;
  size_t n = static_cast<size_t>(world_size);
  size_t step = (count + n - 1) / n;  
  size_t r = static_cast<size_t>(next.rank);
  size_t write_ptr = std::min(r * step, count) * type_nbytes;
  size_t read_ptr = std::min((r + 1) * step, count) * type_nbytes;
  size_t reduce_ptr = read_ptr;
  // send recv buffer
  char *sendrecvbuf = reinterpret_cast<char*>(sendrecvbuf_);
  // position to stop reading
  const size_t stop_read = total_size + write_ptr;
  // position to stop writing
  size_t stop_write = total_size + std::min(rank * step, count) * type_nbytes;
  if (stop_write > stop_read) {
    stop_write -= total_size;
    utils::Assert(write_ptr <= stop_write, "write ptr boundary check");
  }
  // use ring buffer in next position
  next.InitBuffer(type_nbytes, step, reduce_buffer_size);
  // set size_read to read pointer for ring buffer to work properly
  next.size_read = read_ptr;

  while (true) {
    // select helper
    bool finished = true;
    utils::SelectHelper selecter;
    if (read_ptr != stop_read) {
      selecter.WatchRead(next.sock);
      finished = false;
    }
    if (write_ptr != stop_write) {
      if (write_ptr < reduce_ptr) {
        selecter.WatchWrite(prev.sock);
      }
      finished = false;
    }
    if (finished) break;
    selecter.Select();
    if (read_ptr != stop_read && selecter.CheckRead(next.sock)) {
      ReturnType ret = next.ReadToRingBuffer(reduce_ptr, stop_read);
      if (ret != kSuccess) {
        return ReportError(&next, ret);
      }
      // sync the rate
      read_ptr = next.size_read;
      utils::Assert(read_ptr <= stop_read, "[%d] read_ptr boundary check", rank);
      const size_t buffer_size = next.buffer_size;
      size_t max_reduce = (read_ptr  / type_nbytes) * type_nbytes;
      while (reduce_ptr < max_reduce) {
        size_t bstart = reduce_ptr % buffer_size;
        size_t nread = std::min(buffer_size - bstart,
                                max_reduce - reduce_ptr);
        size_t rstart = reduce_ptr % total_size;
        nread = std::min(nread, total_size - rstart);
        reducer(next.buffer_head + bstart,
                sendrecvbuf + rstart,
                static_cast<int>(nread / type_nbytes),
                MPI::Datatype(type_nbytes));
        reduce_ptr += nread;
      }
    }
    if (write_ptr < reduce_ptr && write_ptr != stop_write) {
      size_t size = std::min(reduce_ptr, stop_write) - write_ptr;
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
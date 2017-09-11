void ReduceHandle::AllReduce(void *sendrecvbuf, size_t type_n4bytes, size_t count) {
  utils::Assert(handle != NULL, "must intialize handle to call AllReduce");
  manager.AllReduce(sendrecvbuf, type_n4bytes * 4, count, reinterpret_cast<ReduceFunction*>(handle));
}
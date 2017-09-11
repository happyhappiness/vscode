void ReduceHandle::AllReduce(void *sendrecvbuf, size_t n4byte) {
  utils::Assert(handle != NULL, "must intialize handle to call AllReduce");  
  MPI::Op *op = reinterpret_cast<MPI::Op*>(handle);
  MPI::COMM_WORLD.Allreduce(MPI_IN_PLACE, sendrecvbuf, n4byte, MPI_INT, *op);
}
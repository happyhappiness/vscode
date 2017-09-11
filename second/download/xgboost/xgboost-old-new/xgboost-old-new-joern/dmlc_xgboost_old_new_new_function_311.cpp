e<>
void AllReduce<float>(float *sendrecvbuf, int count, ReduceOp op) {
  typedef float DType;
  switch(op) {
    case kSum: manager.AllReduce(sendrecvbuf, sizeof(DType), count, ReduceSum<DType>); return;
    case kMax: manager.AllReduce(sendrecvbuf, sizeof(DType), count, ReduceMax<DType>); return;
    default: utils::Error("unknown ReduceOp");
  }
}
e<>
void AllReduce<uint32_t>(uint32_t *sendrecvbuf, int count, ReduceOp op) {
  typedef uint32_t DType;
  switch(op) {
    case kBitwiseOR: manager.AllReduce(sendrecvbuf, sizeof(DType), count, ReduceBitOR<DType>); return;
    default: utils::Error("reduce op not supported");
  }
}
  typedef uint32_t DType;
  switch(op) {
    case kBitwiseOR: manager.AllReduce(sendrecvbuf, sizeof(DType), count, ReduceBitOR<DType>); return;
    case kSum: manager.AllReduce(sendrecvbuf, sizeof(DType), count, ReduceSum<DType>); return;
    case kMax: manager.AllReduce(sendrecvbuf, sizeof(DType), count, ReduceMax<DType>); return;
    default: utils::Error("reduce op not supported");
  }
}

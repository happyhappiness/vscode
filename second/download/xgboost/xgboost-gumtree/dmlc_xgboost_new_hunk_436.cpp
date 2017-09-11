  utils::SelectHelper selecter;
};

// singleton sync manager
SyncManager manager;

/*! \brief get rank of current process */
int GetRank(void) {
  return manager.GetRank();
}
/*! \brief get total number of process */
int GetWorldSize(void) {
  return manager.GetWorldSize();
}

/*! \brief get name of processor */
std::string GetProcessorName(void) {
  return manager.GetHost();
}

bool IsDistributed(void) {
  return true;
}
/*! \brief intiialize the synchronization module */
void Init(int argc, char *argv[]) {
  for (int i = 1; i < argc; ++i) {
    char name[256], val[256];
    if (sscanf(argv[i], "%[^=]=%s", name, val) == 2) {
      manager.SetParam(name, val);
    }
  }
  manager.Init();
}

/*! \brief finalize syncrhonization module */
void Finalize(void) {
  manager.Shutdown();
}

// this can only be used for data that was smaller than 64 bit
template<typename DType>
inline void ReduceSum(const void *src_, void *dst_, int len, const MPI::Datatype &dtype) {
  const DType *src = (const DType*)src_;
  DType *dst = (DType*)dst_;  
  for (int i = 0; i < len; ++i) {
    dst[i] += src[i];
  }
}
template<typename DType>
inline void ReduceMax(const void *src_, void *dst_, int len, const MPI::Datatype &dtype) {
  const DType *src = (const DType*)src_;
  DType *dst = (DType*)dst_;  
  for (int i = 0; i < len; ++i) {
    if (src[i] > dst[i]) dst[i] = src[i];
  }
}
template<typename DType>
inline void ReduceBitOR(const void *src_, void *dst_, int len, const MPI::Datatype &dtype) {
  const DType *src = (const DType*)src_;
  DType *dst = (DType*)dst_;  
  for (int i = 0; i < len; ++i) {
    dst[i] |= src[i];
  }
}

template<>
void AllReduce<uint32_t>(uint32_t *sendrecvbuf, int count, ReduceOp op) {
  typedef uint32_t DType;
  switch(op) {
    case kBitwiseOR: manager.AllReduce(sendrecvbuf, sizeof(DType), count, ReduceBitOR<DType>); return;
    default: utils::Error("reduce op not supported");
  }
}

template<>
void AllReduce<float>(float *sendrecvbuf, int count, ReduceOp op) {
  typedef float DType;
  switch(op) {
    case kSum: manager.AllReduce(sendrecvbuf, sizeof(DType), count, ReduceSum<DType>); return;
    case kMax: manager.AllReduce(sendrecvbuf, sizeof(DType), count, ReduceMax<DType>); return;
    default: utils::Error("unknown ReduceOp");
  }
}

void Bcast(std::string *sendrecv_data, int root) {
  unsigned len = static_cast<unsigned>(sendrecv_data->length());
  manager.Bcast(&len, sizeof(len), root);
  sendrecv_data->resize(len);
  if (len != 0) {
    manager.Bcast(&(*sendrecv_data)[0], len, root);  
  }
}

// code for reduce handle
ReduceHandle::ReduceHandle(void) : handle(NULL), htype(NULL) {
}
ReduceHandle::~ReduceHandle(void) {}

int ReduceHandle::TypeSize(const MPI::Datatype &dtype) {
  return dtype.type_size;
}
void ReduceHandle::Init(ReduceFunction redfunc, size_t type_n4bytes, bool commute) {
  utils::Assert(handle == NULL, "cannot initialize reduce handle twice");
  handle = reinterpret_cast<void*>(redfunc);
}
void ReduceHandle::AllReduce(void *sendrecvbuf, size_t type_n4bytes, size_t count) {
  utils::Assert(handle != NULL, "must intialize handle to call AllReduce");
  manager.AllReduce(sendrecvbuf, type_n4bytes * 4, count, reinterpret_cast<ReduceFunction*>(handle));
}

}  // namespace sync
}  // namespace xgboost

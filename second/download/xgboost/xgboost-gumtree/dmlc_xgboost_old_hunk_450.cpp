class Reducer {
 public:
  Reducer(void) {
    handle.Init(ReduceInner);
    utils::Assert(sizeof(DType) % sizeof(int) == 0, "struct must be multiple of int");
  }
  /*!

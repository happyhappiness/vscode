class Reducer {
 public:
  Reducer(void) {
    handle.Init(ReduceInner, kUnit);
    utils::Assert(sizeof(DType) % sizeof(int) == 0, "struct must be multiple of int");
  }
  /*!

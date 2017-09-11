ReduceHandle::~ReduceHandle(void) {}

int ReduceHandle::TypeSize(const MPI::Datatype &dtype) {
  return static_cast<int>(dtype.type_size);
}
void ReduceHandle::Init(ReduceFunction redfunc, size_t type_n4bytes, bool commute) {
  utils::Assert(handle == NULL, "cannot initialize reduce handle twice");

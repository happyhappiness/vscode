void ReduceHandle::Init(ReduceFunction redfunc, bool commute) {
  utils::Assert(handle == NULL, "cannot initialize reduce handle twice");
  MPI::Op *op = new MPI::Op();
  MPI::User_function *pf = reinterpret_cast<MPI::User_function*>(redfunc);
  op->Init(pf, commute);
  handle = op;
}
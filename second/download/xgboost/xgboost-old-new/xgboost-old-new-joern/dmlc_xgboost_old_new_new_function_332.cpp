void ReduceHandle::Init(ReduceFunction redfunc, size_t type_n4bytes, bool commute) {
  utils::Assert(handle == NULL, "cannot initialize reduce handle twice");
  if (type_n4bytes != 0) {
    MPI::Datatype *dtype = new MPI::Datatype();
    *dtype = MPI::INT.Create_contiguous(type_n4bytes);
    dtype->Commit();
    created_type_n4bytes = type_n4bytes;
    htype = dtype;
  }
  
  MPI::Op *op = new MPI::Op();
  MPI::User_function *pf = redfunc;
  op->Init(pf, commute);
  handle = op;
}
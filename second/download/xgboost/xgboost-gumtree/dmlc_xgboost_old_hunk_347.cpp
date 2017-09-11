  utils::Assert(handle_ == NULL, "cannot initialize reduce handle twice");
  if (type_nbytes != 0) {
    MPI::Datatype *dtype = new MPI::Datatype();
    *dtype = MPI::CHAR.Create_contiguous(type_nbytes);
    dtype->Commit();
    created_type_nbytes_ = type_nbytes;
    htype_ = dtype;
  }

  MPI::Op *op = new MPI::Op();
  MPI::User_function *pf = redfunc;
  op->Init(pf, true);

SEXP XGBoosterEvalOneIter_R(SEXP handle, SEXP iter, SEXP dmats, SEXP evnames) {
    utils::Check(length(dmats) == length(evnames), "dmats and evnams must have same length");
    int len = length(dmats);
    std::vector<void*> vec_dmats;
    std::vector<std::string> vec_names;
    std::vector<const char*> vec_sptr;
    for (int i = 0; i < len; ++i){
      vec_dmats.push_back(R_ExternalPtrAddr(VECTOR_ELT(dmats, i)));
      vec_names.push_back(std::string(CHAR(asChar(VECTOR_ELT(evnames, i)))));
      vec_sptr.push_back(vec_names.back().c_str());
    }
    return mkString(XGBoosterEvalOneIter(R_ExternalPtrAddr(handle),
                                         asInteger(iter),
                                         &vec_dmats[0], &vec_sptr[0], len)); 
  }
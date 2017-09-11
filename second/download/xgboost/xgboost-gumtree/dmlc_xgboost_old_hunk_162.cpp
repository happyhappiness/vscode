   *                     will be called by the function before performing Allreduce, to intialize the data in sendrecvbuf_.
   *                     If the result of Allreduce can be recovered directly, then prepare_func will NOT be called
   * \param prepare_arg argument used to passed into the lazy preprocessing function
   */  
  virtual void Allreduce(void *sendrecvbuf_,
                         size_t type_nbytes,
                         size_t count,
                         ReduceFunction reducer,
                         PreprocFunction prepare_fun = NULL,
                         void *prepare_arg = NULL) {
    if (prepare_fun != NULL) prepare_fun(prepare_arg);
    utils::Assert(TryAllreduce(sendrecvbuf_,
                               type_nbytes, count, reducer) == kSuccess,
                  "Allreduce failed");

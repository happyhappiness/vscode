            void (*prepare_fun)(void *arg),
            void *prepare_arg) {
    utils::Error("DataType does not support bitwise or operation");
  }  
};
template<typename OP>
inline void Allreduce_(void *sendrecvbuf_,

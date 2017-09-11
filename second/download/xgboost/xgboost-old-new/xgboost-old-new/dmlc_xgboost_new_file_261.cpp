#ifndef XGBOOST_SYNC_SYNC_H_
#define XGBOOST_SYNC_SYNC_H_
/*!
 * \file sync.h
 * \brief interface to do synchronization
 * \author Tianqi Chen
 */
#include <cstdio>
#include <cstring>
#include "../utils/utils.h"

namespace xgboost {
/*! \brief syncrhonizer module that minimum wraps MPI */
namespace sync {
/*! \brief reduce operator supported */
enum ReduceOp {
  kBitwiseOR,
  kSum
};

typedef void (ReduceFunction) (const void *src, void *dst, int len);

/* !\brief handle for customized reducer */
class ReduceHandle {
 public:
  // constructor
  ReduceHandle(void);
  // destructor
  ~ReduceHandle(void);
  // initialize the reduce function
  void Init(ReduceFunction redfunc, bool commute = true);
  /*!
   * \brief customized in-place all reduce operation 
   * \param sendrecvbuf the in place send-recv buffer
   * \param n4bytes number of nbytes send through all reduce
   */
  void AllReduce(void *sendrecvbuf, size_t n4bytes);
  
 private:
  // handle data field
  void *handle;
};

/*! \brief get rank of current process */
int GetRank(void);
/*! \brief intiialize the synchronization module */
void Init(int argc, char *argv[]);
/*! \brief finalize syncrhonization module */
void Finalize(void);
/*!
 * \brief in-place all reduce operation 
 * \param sendrecvbuf the in place send-recv buffer
 * \param count count of data
 * \param op reduction function
 */
template<typename DType>
void AllReduce(DType *sendrecvbuf, int count, ReduceOp op);

/*! 
 * \brief template class to make customized reduce and all reduce easy  
 * Do not use reducer directly in the function you call Finalize, because the destructor can happen after Finalize
 * \tparam DType data type that to be reduced
 *   DType must be a struct, with no pointer, and contains a function Reduce(const DType &d);
 */
template<typename DType>
class Reducer {
 public:
  Reducer(void) {
    handle.Init(ReduceInner);
    utils::Assert(sizeof(DType) % sizeof(int) == 0, "struct must be multiple of int");
  }
  /*!
   * \brief customized in-place all reduce operation 
   * \param sendrecvbuf the in place send-recv buffer
   * \param bytes number of 4bytes send through all reduce
   * \param reducer the reducer function
   */
  inline void AllReduce(DType *sendrecvbuf, int count) {
    handle.AllReduce(sendrecvbuf, count * kUnit);
  }

 private:
  // unit size 
  static const size_t kUnit = sizeof(DType) / sizeof(int);
  // inner implementation of reducer
  inline static void ReduceInner(const void *src_, void *dst_, int len_) {
    const int *psrc = reinterpret_cast<const int*>(src_);
    int *pdst = reinterpret_cast<int*>(dst_);
    DType tdst, tsrc;
    utils::Assert(len_ % kUnit == 0, "length not divide by size");
    for (size_t i = 0; i < len_; i += kUnit) {
      // use memcpy to avoid alignment issue
      std::memcpy(&tdst, pdst + i, sizeof(tdst));
      std::memcpy(&tsrc, psrc + i, sizeof(tsrc));
      tdst.Reduce(tsrc);
      std::memcpy(pdst + i, &tdst, sizeof(tdst));      
    }
  }
  // function handle
  ReduceHandle handle;
};

}  // namespace sync
}  // namespace xgboost
#endif

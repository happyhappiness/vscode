#ifndef _XGBOOST_SAMPLE_H_
#define _XGBOOST_SAMPLE_H_

#include"../utils/xgboost_utils.h"

namespace xgboost {
  namespace rank {
    namespace sample {

      struct Pairs {

      /*
       * \brief retrieve the related pair information of an data instances
       * \param index, the index of retrieved instance
       * \return the index of instances paired
       */
      std::vector<int> GetPairs(int index) {
        utils::assert(index >= start_ && index < end_, "The query index out of sampling bound");
      }

      std::vector<std::vector<int>> pairs_;
      int start_;
      int end_;
    };

      struct IPairSampler {
	  /*
	   * \brief Generate sample pairs given the predcions, labels, the start and the end index 

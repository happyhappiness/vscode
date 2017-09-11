#ifndef _XGBOOST_SAMPLE_H_
#define _XGBOOST_SAMPLE_H_

#include<vector>
#include"../utils/xgboost_utils.h"

namespace xgboost {
  namespace rank {
    namespace sample {

      /*
       * \brief the data structure to maintain the sample pairs
       */
      struct Pairs {

      /*
       * \brief constructor given the start and end offset of the sampling group
       *        in overall instances
       * \param start the begin index of the group
       * \param end the end index of the group
       */
      Pairs(int start,int end):start_(start),end_(end_){
	for(int i = start; i < end; i++){
	  vector<int> v;
	  pairs_.push_back(v);
	}
      }
      /*
       * \brief retrieve the related pair information of an data instances
       * \param index, the index of retrieved instance
       * \return the index of instances paired
       */
      std::vector<int> GetPairs(int index) {
        utils::assert(index >= start_ && index < end_,"The query index out of sampling bound");
        return pairs_[index-start_];
      }

      /*
       * \brief add in a sampled pair
       * \param index the index of the instance to sample a friend
       * \param paired_index the index of the instance sampled as a friend
       */
      void push(int index,int paired_index){
	pairs_[index - start_].push_back(paired_index);
      }
      
      std::vector<std::vector<int>> pairs_;
      int start_;
      int end_;
    };

      /*
       * \brief the interface of pair sampler
       */
      struct IPairSampler {
	  /*
	   * \brief Generate sample pairs given the predcions, labels, the start and the end index 

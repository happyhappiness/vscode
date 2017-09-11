};

/*!
 * \brief Quantile sketch use WQSummary
 * \tparam DType type of data content
 * \tparam RType type of rank
 */
template<typename DType, typename RType=unsigned>
class WQuantileSketch : 
      public QuantileSketchTemplate<DType, RType, WQSummary<DType, RType> >{
};
/*!
 * \brief Quantile sketch use WQSummary
 * \tparam DType type of data content
 * \tparam RType type of rank
 */
template<typename DType, typename RType=unsigned>
class GKQuantileSketch : 
      public QuantileSketchTemplate<DType, RType, GKSummary<DType, RType> >{
};

}  // utils
}  // xgboost
#endif

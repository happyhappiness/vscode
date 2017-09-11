#include <dmlc/parameter.h>
#include <limits>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include "./base.h"
#include "./data.h"
#include "./feature_map.h"

namespace xgboost {

/*! \brief meta parameters of the tree */
struct TreeParam : public dmlc::Parameter<TreeParam> {
  /*! \brief number of start root */
  int num_roots;
  /*! \brief total number of nodes */
  int num_nodes;
  /*!\brief number of deleted nodes */
  int num_deleted;
  /*! \brief maximum depth, this is a statistics of the tree */
  int max_depth;
  /*! \brief number of features used for tree construction */
  int num_feature;
  /*!
   * \brief leaf vector size, used for vector tree
   * used to store more than one dimensional information in tree
   */
  int size_leaf_vector;
  /*! \brief reserved part, make sure alignment works for 64bit */
  int reserved[31];
  /*! \brief constructor */
  TreeParam() {
    // assert compact alignment
    static_assert(sizeof(TreeParam) == (31 + 6) * sizeof(int),
                  "TreeParam: 64 bit align");
    std::memset(this, 0, sizeof(TreeParam));
    num_nodes = num_roots = 1;
  }
  // declare the parameters
  DMLC_DECLARE_PARAMETER(TreeParam) {
    // only declare the parameters that can be set by the user.
    // other arguments are set by the algorithm.
    DMLC_DECLARE_FIELD(num_roots).set_lower_bound(1).set_default(1)
        .describe("Number of start root of trees.");
    DMLC_DECLARE_FIELD(num_feature)
        .describe("Number of features used in tree construction.");
    DMLC_DECLARE_FIELD(size_leaf_vector).set_lower_bound(0).set_default(0)
        .describe("Size of leaf vector, reserved for vector tree");
  }
};

/*!
 * \brief template class of TreeModel
 * \tparam TSplitCond data type to indicate split condition

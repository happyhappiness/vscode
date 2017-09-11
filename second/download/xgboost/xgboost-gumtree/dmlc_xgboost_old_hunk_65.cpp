#include <dmlc/parameter.h>
#include <limits>
#include <vector>
#include <cstring>
#include <algorithm>
#include "./base.h"

namespace xgboost {
/*!
 * \brief template class of TreeModel
 * \tparam TSplitCond data type to indicate split condition

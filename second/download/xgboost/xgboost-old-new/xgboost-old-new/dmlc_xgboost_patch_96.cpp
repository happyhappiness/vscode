@@ -1,10 +1,12 @@
-#ifndef XGBOOST_UTILS_MATH_H_
-#define XGBOOST_UTILS_MATH_H_
 /*!
+ * Copyright 2014 by Contributors
  * \file math.h
  * \brief support additional math
  * \author Tianqi Chen
  */
+#ifndef XGBOOST_UTILS_MATH_H_
+#define XGBOOST_UTILS_MATH_H_
+
 #include <cmath>
 
 namespace xgboost {
@@ -28,7 +30,8 @@ inline T LogGamma(T v) {
 #if _MSC_VER >= 1800
   return lgamma(v);
 #else
-#pragma message ("Warning: lgamma function was not available until VS2013, poisson regression will be disabled")
+#pragma message("Warning: lgamma function was not available until VS2013"\
+                ", poisson regression will be disabled")
   utils::Error("lgamma function was not available until VS2013");
   return static_cast<T>(1.0);
 #endif
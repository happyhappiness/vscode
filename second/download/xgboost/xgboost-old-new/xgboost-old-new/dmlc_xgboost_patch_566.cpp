@@ -1,8 +1,8 @@
 /*!
- * \file xgboost.cpp
- * \brief bootser implementations 
- * \author Tianqi Chen: tianqi.tchen@gmail.com
- */
+* \file xgboost.cpp
+* \brief bootser implementations 
+* \author Tianqi Chen: tianqi.tchen@gmail.com
+*/
 // implementation of boosters go to here 
 #define _CRT_SECURE_NO_WARNINGS
 #define _CRT_SECURE_NO_DEPRECATE
@@ -15,20 +15,27 @@
 #include "linear/xgboost_linear.hpp"
 
 namespace xgboost{
-    namespace booster{
-        /*! 
-         * \brief create a gradient booster, given type of booster
-         * \param booster_type type of gradient booster, can be used to specify implements
-         * \return the pointer to the gradient booster created
-         */
-        IBooster *CreateBooster( int booster_type ){
-            switch( booster_type ){
-            case 0: return new RTreeTrainer();
-            case 1: return new LinearBooster();
-            default: utils::Error("unknown booster_type"); return NULL;
-            }
-        }
-    };
+	namespace booster{
+		/*��
+		* \brief listing the types of boosters
+		*/
+		enum BOOSTER_TYPE_LIST{
+			TREE,
+			LINEAR,
+		};
+		/*! 
+		* \brief create a gradient booster, given type of booster
+		* \param booster_type type of gradient booster, can be used to specify implements
+		* \return the pointer to the gradient booster created
+		*/
+		IBooster *CreateBooster( int booster_type ){
+			switch( booster_type ){
+			case TREE: return new RTreeTrainer();
+			case LINEAR: return new LinearBooster();
+			default: utils::Error("unknown booster_type"); return NULL;
+			}
+		}
+	};
 };
 
 
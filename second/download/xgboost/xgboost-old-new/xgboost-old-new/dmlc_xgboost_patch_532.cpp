@@ -3,7 +3,9 @@
 /*!
  * \file xgboost.h
  * \brief the general gradient boosting interface
- * 
+ *
+ *   common practice of this header: use IBooster and CreateBooster<FMatrixS>
+ *
  * \author Tianqi Chen: tianqi.tchen@gmail.com
  */
 #include <vector>
@@ -19,8 +21,10 @@ namespace xgboost{
     namespace booster{
         /*! 
          * \brief interface of a gradient boosting learner 
+         * \tparam FMatrix the feature matrix format that the booster takes
          */
-        class IBooster{
+        template<typename FMatrix>
+        class InterfaceBooster{
         public:
             // interface for model setting and loading
             // calling procedure:
@@ -69,21 +73,25 @@ namespace xgboost{
             /*! 
              * \brief predict the path ids along a trees, for given sparse feature vector. When booster is a tree
              * \param path the result of path
-             * \param rid root id of current instance, default = 0
+             * \param feats feature matrix
+             * \param row_index  row index in the feature matrix
+             * \param root_index root id of current instance, default = 0
              */
-            virtual void PredPath( std::vector<int> &path, const FMatrixS::Line &feat, unsigned rid = 0 ){
+            virtual void PredPath( std::vector<int> &path, const FMatrix &feats, 
+                                   bst_uint row_index, unsigned root_index = 0 ){
                 utils::Error( "not implemented" );
             }
             /*! 
              * \brief predict values for given sparse feature vector
              * 
              *   NOTE: in tree implementation, Sparse Predict is OpenMP threadsafe, but not threadsafe in general,
              *         dense version of Predict to ensures threadsafety
-             * \param feat vector in sparse format
-             * \param rid root id of current instance, default = 0
+             * \param feats feature matrix
+             * \param row_index  row index in the feature matrix
+             * \param root_index root id of current instance, default = 0
              * \return prediction 
              */        
-            virtual float Predict( const FMatrixS::Line &feat, unsigned rid = 0 ){
+            virtual float Predict( const FMatrix &feats, bst_uint row_index, unsigned root_index = 0 ){                
                 utils::Error( "not implemented" );
                 return 0.0f;
             }
@@ -92,12 +100,12 @@ namespace xgboost{
              * \param feat feature vector in dense format
              * \param funknown indicator that the feature is missing
              * \param rid root id of current instance, default = 0
-             * \return prediction 
-             */                
+             * \return prediction
+             */
             virtual float Predict( const std::vector<float> &feat, 
                                    const std::vector<bool>  &funknown,
                                    unsigned rid = 0 ){
-                utils::Error( "not implemented" );            
+                utils::Error( "not implemented" );
                 return 0.0f;
             }
             /*! 
@@ -116,19 +124,40 @@ namespace xgboost{
             }
         public:
             /*! \brief virtual destructor */
-            virtual ~IBooster( void ){}
-        };    
+            virtual ~InterfaceBooster( void ){}
+        };
+    };
+    namespace booster{
+        /*! 
+         * \brief this will is the most commonly used booster interface 
+         *  we try to make booster invariant of data structures, but most cases, FMatrixS is what we wnat
+         */
+        typedef InterfaceBooster<FMatrixS> IBooster;
     };
 };
 
 namespace xgboost{
     namespace booster{
         /*! 
          * \brief create a gradient booster, given type of booster
+         *    normally we use FMatrixS, by calling CreateBooster<FMatrixS>
          * \param booster_type type of gradient booster, can be used to specify implements
+         * \tparam FMatrix input data type for booster
          * \return the pointer to the gradient booster created
          */
-        IBooster *CreateBooster( int booster_type );
+        template<typename FMatrix>
+        inline InterfaceBooster<FMatrix> *CreateBooster( int booster_type );
     };
 };
+
+// A good design should have minimum functions defined interface, user should only operate on interface
+// I break it a bit, by using template and let user 'see' the implementation
+// The user should pretend that they only can use the interface, and we are all cool
+// I find this is the only way so far I can think of to make boosters invariant of data structure, 
+// while keep everything fast
+
+// this file includes the template implementations of all boosters
+// the cost of using template is that the user can 'see' all the implementations, which is OK 
+// ignore implementations and focus on the interface:) 
+#include "xgboost-inl.hpp"
 #endif
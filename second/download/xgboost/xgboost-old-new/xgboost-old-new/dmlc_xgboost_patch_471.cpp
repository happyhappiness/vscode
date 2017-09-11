@@ -19,8 +19,8 @@
 namespace xgboost{
     /*! \brief namespace for boosters */
     namespace booster{
-        /*! 
-         * \brief interface of a gradient boosting learner 
+        /*!
+         * \brief interface of a gradient boosting learner
          * \tparam FMatrix the feature matrix format that the booster takes
          */
         template<typename FMatrix>
@@ -35,101 +35,101 @@ namespace xgboost{
             //          call booster->LoadModel
             //  (3) booster->DoBoost to update the model
             //  (4) booster->Predict to get new prediction
-            /*! 
-             * \brief set parameters from outside 
+            /*!
+             * \brief set parameters from outside
              * \param name name of the parameter
              * \param val  value of the parameter
              */
-            virtual void SetParam( const char *name, const char *val ) = 0;
-            /*! 
+            virtual void SetParam(const char *name, const char *val) = 0;
+            /*!
              * \brief load model from stream
              * \param fi input stream
              */
-            virtual void LoadModel( utils::IStream &fi ) = 0;
-            /*! 
+            virtual void LoadModel(utils::IStream &fi) = 0;
+            /*!
              * \brief save model to stream
              * \param fo output stream
              */
-            virtual void SaveModel( utils::IStream &fo ) const = 0;
+            virtual void SaveModel(utils::IStream &fo) const = 0;
             /*!
              * \brief initialize solver before training, called before training
-             * this function is reserved for solver to allocate necessary space and do other preparation 
+             * this function is reserved for solver to allocate necessary space and do other preparation
              */
-            virtual void InitModel( void ) = 0;
+            virtual void InitModel(void) = 0;
         public:
-            /*! 
-             * \brief do gradient boost training for one step, using the information given, 
+            /*!
+             * \brief do gradient boost training for one step, using the information given,
              *        Note: content of grad and hess can change after DoBoost
              * \param grad first order gradient of each instance
              * \param hess second order gradient of each instance
              * \param feats features of each instance
-             * \param root_index pre-partitioned root index of each instance, 
+             * \param root_index pre-partitioned root index of each instance,
              *          root_index.size() can be 0 which indicates that no pre-partition involved
              */
-            virtual void DoBoost( std::vector<float> &grad,
-                                  std::vector<float> &hess,
-                                  const FMatrix &feats,
-                                  const std::vector<unsigned> &root_index ) = 0;
-            /*! 
+            virtual void DoBoost(std::vector<float> &grad,
+                std::vector<float> &hess,
+                const FMatrix &feats,
+                const std::vector<unsigned> &root_index) = 0;
+            /*!
              * \brief predict the path ids along a trees, for given sparse feature vector. When booster is a tree
              * \param path the result of path
              * \param feats feature matrix
              * \param row_index  row index in the feature matrix
              * \param root_index root id of current instance, default = 0
              */
-            virtual void PredPath( std::vector<int> &path, const FMatrix &feats, 
-                                   bst_uint row_index, unsigned root_index = 0 ){
-                utils::Error( "not implemented" );
+            virtual void PredPath(std::vector<int> &path, const FMatrix &feats,
+                bst_uint row_index, unsigned root_index = 0){
+                utils::Error("not implemented");
             }
-            /*! 
+            /*!
              * \brief predict values for given sparse feature vector
-             * 
+             *
              *   NOTE: in tree implementation, Sparse Predict is OpenMP threadsafe, but not threadsafe in general,
              *         dense version of Predict to ensures threadsafety
              * \param feats feature matrix
              * \param row_index  row index in the feature matrix
              * \param root_index root id of current instance, default = 0
-             * \return prediction 
-             */        
-            virtual float Predict( const FMatrix &feats, bst_uint row_index, unsigned root_index = 0 ){                
-                utils::Error( "not implemented" );
+             * \return prediction
+             */
+            virtual float Predict(const FMatrix &feats, bst_uint row_index, unsigned root_index = 0){
+                utils::Error("not implemented");
                 return 0.0f;
             }
-            /*! 
+            /*!
              * \brief predict values for given dense feature vector
              * \param feat feature vector in dense format
              * \param funknown indicator that the feature is missing
              * \param rid root id of current instance, default = 0
              * \return prediction
              */
-            virtual float Predict( const std::vector<float> &feat, 
-                                   const std::vector<bool>  &funknown,
-                                   unsigned rid = 0 ){
-                utils::Error( "not implemented" );
+            virtual float Predict(const std::vector<float> &feat,
+                const std::vector<bool>  &funknown,
+                unsigned rid = 0){
+                utils::Error("not implemented");
                 return 0.0f;
             }
-            /*! 
+            /*!
              * \brief print information
-             * \param fo output stream 
-             */        
-            virtual void PrintInfo( FILE *fo ){}
-            /*! 
+             * \param fo output stream
+             */
+            virtual void PrintInfo(FILE *fo){}
+            /*!
              * \brief dump model into text file
-             * \param fo output stream 
+             * \param fo output stream
              * \param fmap feature map that may help give interpretations of feature
              * \param with_stats whether print statistics
              */
-            virtual void DumpModel( FILE *fo, const utils::FeatMap& fmap, bool with_stats = false ){
-                utils::Error( "not implemented" );                
+            virtual void DumpModel(FILE *fo, const utils::FeatMap& fmap, bool with_stats = false){
+                utils::Error("not implemented");
             }
         public:
             /*! \brief virtual destructor */
-            virtual ~InterfaceBooster( void ){}
+            virtual ~InterfaceBooster(void){}
         };
     };
     namespace booster{
-        /*! 
-         * \brief this will is the most commonly used booster interface 
+        /*!
+         * \brief this will is the most commonly used booster interface
          *  we try to make booster invariant of data structures, but most cases, FMatrixS is what we wnat
          */
         typedef InterfaceBooster<FMatrixS> IBooster;
@@ -138,15 +138,15 @@ namespace xgboost{
 
 namespace xgboost{
     namespace booster{
-        /*! 
+        /*!
          * \brief create a gradient booster, given type of booster
          *    normally we use FMatrixS, by calling CreateBooster<FMatrixS>
          * \param booster_type type of gradient booster, can be used to specify implements
          * \tparam FMatrix input data type for booster
          * \return the pointer to the gradient booster created
          */
         template<typename FMatrix>
-        inline InterfaceBooster<FMatrix> *CreateBooster( int booster_type );
+        inline InterfaceBooster<FMatrix> *CreateBooster(int booster_type);
     };
 };
 
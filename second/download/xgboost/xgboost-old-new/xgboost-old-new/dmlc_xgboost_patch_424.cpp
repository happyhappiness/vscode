@@ -88,8 +88,8 @@ namespace xgboost{
                     }
                 }
                 if (mparam.num_pbuffer != 0){
-                    pred_buffer.resize(mparam.num_pbuffer);
-                    pred_counter.resize(mparam.num_pbuffer);
+                    pred_buffer.resize(mparam.PredBufferSize());
+                    pred_counter.resize(mparam.PredBufferSize());
                     utils::Assert(fi.Read(&pred_buffer[0], pred_buffer.size()*sizeof(float)) != 0);
                     utils::Assert(fi.Read(&pred_counter[0], pred_counter.size()*sizeof(unsigned)) != 0);
                 }
@@ -117,8 +117,8 @@ namespace xgboost{
              */
             inline void InitModel(void){
                 pred_buffer.clear(); pred_counter.clear();
-                pred_buffer.resize(mparam.num_pbuffer, 0.0);
-                pred_counter.resize(mparam.num_pbuffer, 0);
+                pred_buffer.resize(mparam.PredBufferSize(), 0.0);
+                pred_counter.resize(mparam.PredBufferSize(), 0);
                 utils::Assert(mparam.num_boosters == 0);
                 utils::Assert(boosters.size() == 0);
             }
@@ -130,6 +130,7 @@ namespace xgboost{
                 if (tparam.nthread != 0){
                     omp_set_num_threads(tparam.nthread);
                 }
+                if (mparam.num_booster_group == 0) mparam.num_booster_group = 1;
                 // make sure all the boosters get the latest parameters
                 for (size_t i = 0; i < this->boosters.size(); i++){
                     this->ConfigBooster(this->boosters[i]);
@@ -175,12 +176,14 @@ namespace xgboost{
              * \param feats features of each instance
              * \param root_index pre-partitioned root index of each instance,
              *          root_index.size() can be 0 which indicates that no pre-partition involved
+             * \param bst_group which booster group it belongs to, by default, we only have 1 booster group, and leave this parameter as default
              */
             inline void DoBoost(std::vector<float> &grad,
                                 std::vector<float> &hess,
                                 const booster::FMatrixS &feats,
-                                const std::vector<unsigned> &root_index) {
-                booster::IBooster *bst = this->GetUpdateBooster();
+                                const std::vector<unsigned> &root_index,
+                                int bst_group = 0 ) {
+                booster::IBooster *bst = this->GetUpdateBooster( bst_group );
                 bst->DoBoost(grad, hess, feats, root_index);
             }
             /*!
@@ -190,48 +193,60 @@ namespace xgboost{
              * \param row_index  row index in the feature matrix
              * \param buffer_index the buffer index of the current feature line, default -1 means no buffer assigned
              * \param root_index root id of current instance, default = 0
+             * \param bst_group booster group index 
              * \return prediction
              */
-            inline float Predict(const FMatrixS &feats, bst_uint row_index, int buffer_index = -1, unsigned root_index = 0){
-                size_t istart = 0;
+            inline float Predict(const FMatrixS &feats, bst_uint row_index, 
+                                 int buffer_index = -1, unsigned root_index = 0, int bst_group = 0 ){
+                size_t itop = 0;
                 float  psum = 0.0f;
+                const int bid = mparam.BufferOffset(buffer_index, bst_group);
 
                 // load buffered results if any
-                if (mparam.do_reboost == 0 && buffer_index >= 0){
-                    utils::Assert(buffer_index < mparam.num_pbuffer, "buffer index exceed num_pbuffer");
-                    istart = this->pred_counter[buffer_index];
-                    psum = this->pred_buffer[buffer_index];
+                if (mparam.do_reboost == 0 && bid >= 0){
+                    itop = this->pred_counter[bid];
+                    psum = this->pred_buffer[bid];
                 }
 
-                for (size_t i = istart; i < this->boosters.size(); i++){
-                    psum += this->boosters[i]->Predict(feats, row_index, root_index);
+                for (size_t i = itop; i < this->boosters.size(); ++i ){
+                    if( booster_info[i] == bst_group ){
+                        psum += this->boosters[i]->Predict(feats, row_index, root_index);
+                    }
                 }
                 // updated the buffered results
-                if (mparam.do_reboost == 0 && buffer_index >= 0){
-                    this->pred_counter[buffer_index] = static_cast<unsigned>(boosters.size());
-                    this->pred_buffer[buffer_index] = psum;
+                if (mparam.do_reboost == 0 && bid >= 0){
+                    this->pred_counter[bid] = static_cast<unsigned>(boosters.size());
+                    this->pred_buffer[bid] = psum;
                 }
                 return psum;
             }
             /*! \return number of boosters so far */
             inline int NumBoosters(void) const{
                 return mparam.num_boosters;
             }
+            /*! \return number of booster groups */
+            inline int NumBoosterGroup(void) const{
+                if( mparam.num_booster_group == 0 ) return 1;
+                return mparam.num_booster_group;
+            }
         public:
             //--------trial code for interactive update an existing booster------
             //-------- usually not needed, ignore this region ---------
             /*!
              * \brief same as Predict, but removes the prediction of booster to be updated
              *        this function must be called once and only once for every data with pbuffer
              */
-            inline float InteractPredict(const FMatrixS &feats, bst_uint row_index, int buffer_index = -1, unsigned root_index = 0){
+            inline float InteractPredict(const FMatrixS &feats, bst_uint row_index, 
+                                         int buffer_index = -1, unsigned root_index = 0, int bst_group = 0){
                 float psum = this->Predict(feats, row_index, buffer_index, root_index);
                 if (tparam.reupdate_booster != -1){
                     const int bid = tparam.reupdate_booster;
                     utils::Assert(bid >= 0 && bid < (int)boosters.size(), "interact:booster_index exceed existing bound");
-                    psum -= boosters[bid]->Predict(feats, row_index, root_index);
+                    if( bst_group == booster_info[bid] ){
+                        psum -= boosters[bid]->Predict(feats, row_index, root_index);
+                    }
                     if (mparam.do_reboost == 0 && buffer_index >= 0){
-                        this->pred_buffer[buffer_index] = psum;
+                        this->pred_buffer[mparam.BufferOffset(buffer_index,bst_group)] = psum;
                     }
                 }
                 return psum;
@@ -246,15 +261,21 @@ namespace xgboost{
                     booster_info[i - 1] = booster_info[i];
                 }
                 boosters.resize(mparam.num_boosters -= 1);
-                booster_info.resize(boosters.size());
+                booster_info.resize(boosters.size());                
+                // update pred counter
+                for( size_t i = 0; i < pred_counter.size(); ++ i ){
+                    if( pred_counter[i] > (unsigned)bid ) pred_counter[i] -= 1;                    
+                }
             }
             /*! \brief update the prediction buffer, after booster have been updated */
-            inline void InteractRePredict(const FMatrixS &feats, bst_uint row_index, int buffer_index = -1, unsigned root_index = 0){
+            inline void InteractRePredict(const FMatrixS &feats, bst_uint row_index, 
+                                          int buffer_index = -1, unsigned root_index = 0, int bst_group = 0 ){
                 if (tparam.reupdate_booster != -1){
                     const int bid = tparam.reupdate_booster;
+                    if( booster_info[bid]  != bst_group ) return;
                     utils::Assert(bid >= 0 && bid < (int)boosters.size(), "interact:booster_index exceed existing bound");
                     if (mparam.do_reboost == 0 && buffer_index >= 0){
-                        this->pred_buffer[buffer_index] += boosters[bid]->Predict(feats, row_index, root_index);
+                        this->pred_buffer[mparam.BufferOffset(buffer_index,bst_group)] += boosters[bid]->Predict(feats, row_index, root_index);
                     }
                 }
             }
@@ -278,18 +299,19 @@ namespace xgboost{
              * \brief get a booster to update
              * \return the booster created
              */
-            inline booster::IBooster *GetUpdateBooster(void){
+            inline booster::IBooster *GetUpdateBooster(int bst_group){
                 if (tparam.reupdate_booster != -1){
                     const int bid = tparam.reupdate_booster;
                     utils::Assert(bid >= 0 && bid < (int)boosters.size(), "interact:booster_index exceed existing bound");
                     this->ConfigBooster(boosters[bid]);
+                    utils::Assert( bst_group == booster_info[bid], "booster group must match existing reupdate booster");
                     return boosters[bid];
                 }
 
                 if (mparam.do_reboost == 0 || boosters.size() == 0){
                     mparam.num_boosters += 1;
                     boosters.push_back(booster::CreateBooster<FMatrixS>(mparam.booster_type));
-                    booster_info.push_back(0);
+                    booster_info.push_back(bst_group);
                     this->ConfigBooster(boosters.back());
                     boosters.back()->InitModel();
                 }
@@ -316,15 +338,21 @@ namespace xgboost{
                  *        set to 1 for linear booster, so that regularization term can be considered
                  */
                 int do_reboost;
+                /*! 
+                 * \brief number of booster group, how many predictions a single 
+                 *        input instance could corresponds to
+                 */
+                int num_booster_group;
                 /*! \brief reserved parameters */
-                int reserved[32];
+                int reserved[31];
                 /*! \brief constructor */
                 ModelParam(void){
                     num_boosters = 0;
                     booster_type = 0;
                     num_roots = num_feature = 0;
                     do_reboost = 0;
                     num_pbuffer = 0;
+                    num_booster_group = 1;
                     memset(reserved, 0, sizeof(reserved));
                 }
                 /*!
@@ -338,10 +366,21 @@ namespace xgboost{
                         // linear boost automatically set do reboost
                         if (booster_type == 1) do_reboost = 1;
                     }
-                    if (!strcmp("num_pbuffer", name))      num_pbuffer = atoi(val);
-                    if (!strcmp("do_reboost", name))       do_reboost = atoi(val);
-                    if (!strcmp("bst:num_roots", name))    num_roots = atoi(val);
-                    if (!strcmp("bst:num_feature", name))  num_feature = atoi(val);
+                    if (!strcmp("num_pbuffer", name))       num_pbuffer = atoi(val);
+                    if (!strcmp("do_reboost", name))        do_reboost = atoi(val);
+                    if (!strcmp("num_booster_group", name)) num_booster_group = atoi(val);
+                    if (!strcmp("bst:num_roots", name))     num_roots = atoi(val);
+                    if (!strcmp("bst:num_feature", name))   num_feature = atoi(val);
+                }
+                inline int PredBufferSize(void) const{
+                    if (num_booster_group == 0) return num_pbuffer;
+                    else return num_booster_group * num_pbuffer;
+                }
+                inline int BufferOffset( int buffer_index, int bst_group ) const{
+                    if( buffer_index < 0 ) return -1;
+                    utils::Assert( buffer_index < num_pbuffer, "buffer_indexexceed num_pbuffer" ); 
+                    return buffer_index + num_pbuffer * bst_group;
+                    
                 }
             };
             /*! \brief training parameters */
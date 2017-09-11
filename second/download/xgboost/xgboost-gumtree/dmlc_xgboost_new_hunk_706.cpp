             * \param row_index  row index in the feature matrix
             * \param buffer_index the buffer index of the current feature line, default -1 means no buffer assigned
             * \param root_index root id of current instance, default = 0
             * \param bst_group booster group index 
             * \return prediction
             */
            inline float Predict(const FMatrixS &feats, bst_uint row_index, 
                                 int buffer_index = -1, unsigned root_index = 0, int bst_group = 0 ){
                size_t itop = 0;
                float  psum = 0.0f;
                const int bid = mparam.BufferOffset(buffer_index, bst_group);

                // load buffered results if any
                if (mparam.do_reboost == 0 && bid >= 0){
                    itop = this->pred_counter[bid];
                    psum = this->pred_buffer[bid];
                }

                for (size_t i = itop; i < this->boosters.size(); ++i ){
                    if( booster_info[i] == bst_group ){
                        psum += this->boosters[i]->Predict(feats, row_index, root_index);
                    }
                }
                // updated the buffered results
                if (mparam.do_reboost == 0 && bid >= 0){
                    this->pred_counter[bid] = static_cast<unsigned>(boosters.size());
                    this->pred_buffer[bid] = psum;
                }
                return psum;
            }
            /*! \return number of boosters so far */
            inline int NumBoosters(void) const{
                return mparam.num_boosters;
            }
            /*! \return number of booster groups */
            inline int NumBoosterGroup(void) const{
                if( mparam.num_booster_group == 0 ) return 1;
                return mparam.num_booster_group;
            }
        public:
            //--------trial code for interactive update an existing booster------
            //-------- usually not needed, ignore this region ---------
            /*!
             * \brief same as Predict, but removes the prediction of booster to be updated
             *        this function must be called once and only once for every data with pbuffer
             */
            inline float InteractPredict(const FMatrixS &feats, bst_uint row_index, 
                                         int buffer_index = -1, unsigned root_index = 0, int bst_group = 0){
                float psum = this->Predict(feats, row_index, buffer_index, root_index);
                if (tparam.reupdate_booster != -1){
                    const int bid = tparam.reupdate_booster;
                    utils::Assert(bid >= 0 && bid < (int)boosters.size(), "interact:booster_index exceed existing bound");
                    if( bst_group == booster_info[bid] ){
                        psum -= boosters[bid]->Predict(feats, row_index, root_index);
                    }
                    if (mparam.do_reboost == 0 && buffer_index >= 0){
                        this->pred_buffer[mparam.BufferOffset(buffer_index,bst_group)] = psum;
                    }
                }
                return psum;

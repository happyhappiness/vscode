             * \param row_index  row index in the feature matrix
             * \param buffer_index the buffer index of the current feature line, default -1 means no buffer assigned
             * \param root_index root id of current instance, default = 0
             * \return prediction
             */
            inline float Predict(const FMatrixS &feats, bst_uint row_index, int buffer_index = -1, unsigned root_index = 0){
                size_t istart = 0;
                float  psum = 0.0f;

                // load buffered results if any
                if (mparam.do_reboost == 0 && buffer_index >= 0){
                    utils::Assert(buffer_index < mparam.num_pbuffer, "buffer index exceed num_pbuffer");
                    istart = this->pred_counter[buffer_index];
                    psum = this->pred_buffer[buffer_index];
                }

                for (size_t i = istart; i < this->boosters.size(); i++){
                    psum += this->boosters[i]->Predict(feats, row_index, root_index);
                }
                // updated the buffered results
                if (mparam.do_reboost == 0 && buffer_index >= 0){
                    this->pred_counter[buffer_index] = static_cast<unsigned>(boosters.size());
                    this->pred_buffer[buffer_index] = psum;
                }
                return psum;
            }
            /*! \return number of boosters so far */
            inline int NumBoosters(void) const{
                return mparam.num_boosters;
            }
        public:
            //--------trial code for interactive update an existing booster------
            //-------- usually not needed, ignore this region ---------
            /*!
             * \brief same as Predict, but removes the prediction of booster to be updated
             *        this function must be called once and only once for every data with pbuffer
             */
            inline float InteractPredict(const FMatrixS &feats, bst_uint row_index, int buffer_index = -1, unsigned root_index = 0){
                float psum = this->Predict(feats, row_index, buffer_index, root_index);
                if (tparam.reupdate_booster != -1){
                    const int bid = tparam.reupdate_booster;
                    utils::Assert(bid >= 0 && bid < (int)boosters.size(), "interact:booster_index exceed existing bound");
                    psum -= boosters[bid]->Predict(feats, row_index, root_index);
                    if (mparam.do_reboost == 0 && buffer_index >= 0){
                        this->pred_buffer[buffer_index] = psum;
                    }
                }
                return psum;

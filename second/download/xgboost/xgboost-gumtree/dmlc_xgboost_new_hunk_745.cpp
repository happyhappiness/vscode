                this->info.labels.resize( len );
                memcpy( &(this->info).labels[0], label, sizeof(float)*len );
            }
            inline void SetGroup( const unsigned *group, size_t len ){
                this->info.group_ptr.resize( len + 1 );
                this->info.group_ptr[0] = 0;
                for( size_t i = 0; i < len; ++ i ){
                    this->info.group_ptr[i+1] = this->info.group_ptr[i]+group[i];
                }
            }
            inline void SetWeight( const float *weight, size_t len ){
                this->info.weights.resize( len );
                memcpy( &(this->info).weights[0], weight, sizeof(float)*len );
            }
            inline const float* GetLabel( size_t* len ) const{
                *len = this->info.labels.size();
                return &(this->info.labels[0]);
            }
            inline void CheckInit(void){
                if(!this->data.HaveColAccess()){
                    this->data.InitData();
                }
                utils::Assert( this->data.NumRow() == this->info.labels.size(), "DMatrix: number of labels must match number of rows in matrix");
            }
        };
    
        class Booster: public xgboost::regrank::RegRankBoostLearner{
        private:
            bool init_trainer, init_model;
        public:
            Booster(const std::vector<const regrank::DMatrix *> mats){
                silent = 1;
                init_trainer = false;
                init_model = false;
                this->SetCacheData(mats);
            }
            inline void CheckInit(void){
                if( !init_trainer ){
                    this->InitTrainer(); init_trainer = true;
                }
                if( !init_model ){
                    this->InitModel(); init_model = true;
                }
            }
            inline void LoadModel( const char *fname ){
                xgboost::regrank::RegRankBoostLearner::LoadModel(fname);
                this->init_model = true;
            }
            const float *Pred( const DMatrix &dmat, size_t *len ){
                this->Predict( this->preds_, dmat );
                *len = this->preds_.size();
                return &this->preds_[0];
            }
        };
    };
};

using namespace xgboost::python;


extern "C"{
    void* XGDMatrixCreate( void ){
        return new DMatrix();

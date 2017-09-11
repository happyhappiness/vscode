                this->info.labels.resize( len );
                memcpy( &(this->info).labels[0], label, sizeof(float)*len );
            }
            inline const float* GetLabel( size_t* len ) const{
                *len = this->info.labels.size();
                return &(this->info.labels[0]);
            }
            inline void InitTrain(void){
                if(!this->data.HaveColAccess()) this->data.InitData();
                utils::Assert( this->data.NumRow() == this->info.labels.size(), "DMatrix: number of labels must match number of rows in matrix");
            }
        };
    };
};

using namespace xgboost::python;

extern "C"{
    void* XGDMatrixCreate( void ){
        return new DMatrix();

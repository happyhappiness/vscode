            inline void CheckInit(void){
                if(!init_col_){
                    this->data.InitData();
                }
                utils::Assert( this->data.NumRow() == this->info.labels.size(), "DMatrix: number of labels must match number of rows in matrix");
            }

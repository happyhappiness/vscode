                return &(this->info.labels[0]);
            }
            inline void CheckInit(void){
                if(!this->data.HaveColAccess()){
                    this->data.InitData();
                }
                utils::Assert( this->data.NumRow() == this->info.labels.size(), "DMatrix: number of labels must match number of rows in matrix");

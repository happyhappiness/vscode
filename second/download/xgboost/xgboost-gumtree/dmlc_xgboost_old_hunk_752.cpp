                this->CacheLoad(fname, silent);
                init_col_ = this->data.HaveColAccess();
            }
        };
    };
};

using namespace xgboost::python;

extern "C"{
    void* XGDMatrixCreate(void){
        return new DMatrix();
    }
    void XGDMatrixFree(void *handle){
        delete static_cast<DMatrix*>(handle);
    }
    void XGDMatrixLoad(void *handle, const char *fname, int silent){
        static_cast<DMatrix*>(handle)->Load(fname, silent!=0);
    }
    void XGDMatrixSaveBinary(void *handle, const char *fname, int silent){
        static_cast<DMatrix*>(handle)->SaveBinary(fname, silent!=0);
    }
};


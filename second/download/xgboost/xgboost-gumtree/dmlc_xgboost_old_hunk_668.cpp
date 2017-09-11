            inline float SecondOrderGradient(float predt, float label) const{
                switch (loss_type){
                case kLinearSquare: return 1.0f;
                case kLogisticClassify:
                case kLogisticNeglik: return predt * (1 - predt);
                default: utils::Error("unknown loss_type"); return 0.0f;

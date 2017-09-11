            inline float SecondOrderGradient(float predt, float label) const{
                switch (loss_type){
                case kLinearSquare: return 1.0f;
                case kLogisticRaw: predt = 1.0f / (1.0f + expf(-predt));
                case kLogisticClassify:
                case kLogisticNeglik: return predt * (1 - predt);
                default: utils::Error("unknown loss_type"); return 0.0f;

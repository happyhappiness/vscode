            inline float FirstOrderGradient(float predt, float label) const{
                switch (loss_type){
                case kLinearSquare: return predt - label;
                case kLogisticRaw: predt = 1.0f / (1.0f + expf(-predt));
                case kLogisticClassify:
                case kLogisticNeglik: return predt - label;
                default: utils::Error("unknown loss_type"); return 0.0f;

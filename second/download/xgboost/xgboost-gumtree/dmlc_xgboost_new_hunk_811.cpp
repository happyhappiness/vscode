                /* \brief number of features  */
                int num_feature;
                /*! \brief reserved field */
                int reserved[16];
                /*! \brief constructor */
                ModelParam(void){
                    base_score = 0.5f;
                    loss_type = 0;
                    num_feature = 0;
                    memset(reserved, 0, sizeof(reserved));
                }
                /*!
                * \brief set parameters from outside
                * \param name name of the parameter
                * \param val  value of the parameter
                */
                inline void SetParam(const char *name, const char *val){
                    if (!strcmp("base_score", name))  base_score = (float)atof(val);
                    if (!strcmp("loss_type", name))   loss_type = atoi(val);
                    if (!strcmp("bst:num_feature", name)) num_feature = atoi(val);
                }
                /*!
                * \brief adjust base_score
                */
                inline void AdjustBase(void){
                    if (loss_type == 1 || loss_type == 2){
                        utils::Assert(base_score > 0.0f && base_score < 1.0f, "sigmoid range constrain");
                        base_score = -logf(1.0f / base_score - 1.0f);
                    }
                }

                /*!
                * \brief transform the linear sum to prediction
                * \param x linear sum of boosting ensemble
                * \return transformed prediction
                */
                inline float PredTransform(float x){
                    switch (loss_type){
                    case kLinearSquare: return x;
                    case kLogisticClassify:
                    case kLogisticNeglik: return 1.0f / (1.0f + expf(-x));
                    default: utils::Error("unknown loss_type"); return 0.0f;
                    }
                }

                /*!
                * \brief calculate first order gradient of loss, given transformed prediction
                * \param predt transformed prediction
                * \param label true label
                * \return first order gradient
                */
                inline float FirstOrderGradient(float predt, float label) const{
                    switch (loss_type){
                    case kLinearSquare: return predt - label;
                    case kLogisticClassify:
                    case kLogisticNeglik: return predt - label;
                    default: utils::Error("unknown loss_type"); return 0.0f;
                    }
                }
                /*!
                * \brief calculate second order gradient of loss, given transformed prediction
                * \param predt transformed prediction
                * \param label true label
                * \return second order gradient
                */
                inline float SecondOrderGradient(float predt, float label) const{
                    switch (loss_type){
                    case kLinearSquare: return 1.0f;
                    case kLogisticClassify:
                    case kLogisticNeglik: return predt * (1 - predt);
                    default: utils::Error("unknown loss_type"); return 0.0f;
                    }
                }

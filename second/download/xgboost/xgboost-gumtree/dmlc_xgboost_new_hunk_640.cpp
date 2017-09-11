                 */
                inline void SetParam(const char *name, const char *val){
                    if (!strcmp("base_score", name))  base_score = (float)atof(val);
                    if (!strcmp("num_class", name))   num_class = atoi(val);
                    if (!strcmp("loss_type", name))   loss_type = atoi(val);
                    if (!strcmp("bst:num_feature", name)) num_feature = atoi(val);
                }
                /*!
                * \brief adjust base_score based on loss type and objective function
                */
                inline void AdjustBase(const char *obj){
                    // some tweaks for loss type
                    if( loss_type == -1 ){
                        loss_type = 1;
                        if( !strcmp("reg:linear", obj ) ) loss_type = 0;
                    }
                    if (loss_type == 1 || loss_type == 2|| loss_type == 3){
                        utils::Assert(base_score > 0.0f && base_score < 1.0f, "sigmoid range constrain");
                        base_score = -logf(1.0f / base_score - 1.0f);

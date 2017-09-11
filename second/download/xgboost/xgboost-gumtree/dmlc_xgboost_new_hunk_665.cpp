                * \brief adjust base_score
                */
                inline void AdjustBase(void){
                    if (loss_type == 1 || loss_type == 2|| loss_type == 3){
                        utils::Assert(base_score > 0.0f && base_score < 1.0f, "sigmoid range constrain");
                        base_score = -logf(1.0f / base_score - 1.0f);
                    }

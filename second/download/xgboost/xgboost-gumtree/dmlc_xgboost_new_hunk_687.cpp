             */
            inline void InitModel(void){
                pred_buffer.clear(); pred_counter.clear();
                pred_buffer.resize(mparam.PredBufferSize(), 0.0);
                pred_counter.resize(mparam.PredBufferSize(), 0);
                utils::Assert(mparam.num_boosters == 0);
                utils::Assert(boosters.size() == 0);
            }

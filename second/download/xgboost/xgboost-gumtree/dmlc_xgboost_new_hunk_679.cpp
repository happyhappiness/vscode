                    #pragma omp parallel for schedule( static )
                    for (unsigned j = 0; j < ndata; ++j){
                        preds[j] = mparam.base_score + base_gbm.Predict(data.data, j, buffer_offset + j, data.info.GetRoot(j), bst_group );

                    }
                }else
                    #pragma omp parallel for schedule( static )

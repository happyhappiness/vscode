virtual void GetGradient(const std::vector<float>& preds,
                const DMatrix::Info &info,
                int iter,
                std::vector<float> &grad,
                std::vector<float> &hess) {
                grad.resize(preds.size()); hess.resize(preds.size());
                const std::vector<unsigned> &group_index = info.group_ptr;
                utils::Assert(group_index.size() != 0 && group_index.back() == preds.size(), "rank loss must have group file");
                
                for (int i = 0; i < group_index.size() - 1; i++){
                    sample::Pairs pairs = sampler_.GenPairs(preds, info.labels, group_index[i], group_index[i + 1]);
                    //pairs.GetPairs()
                    std::vector< std::tuple<float, float, int> > sorted_triple = GetSortedTuple(preds, info.labels, group_index, i);
                    std::vector<int> index_remap = GetIndexMap(sorted_triple, group_index[i]);
                    GetGroupGradient(preds, info.labels, group_index,
                        grad, hess, sorted_triple, index_remap, pairs, i);
                }
            }
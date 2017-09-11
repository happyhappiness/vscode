                std::vector<unsigned> tgptr(2,0); tgptr[1] = preds.size();
                const std::vector<unsigned> &gptr = info.group_ptr.size() == 0 ? tgptr : info.group_ptr;
                utils::Assert( gptr.back() == preds.size(), "EvalAuc: group structure must match number of prediction" );
                const unsigned ngroup = static_cast<unsigned>( gptr.size() );
            
                double sum_auc = 0.0f;
                #pragma omp parallel reduction(+:sum_auc) 
                {                   

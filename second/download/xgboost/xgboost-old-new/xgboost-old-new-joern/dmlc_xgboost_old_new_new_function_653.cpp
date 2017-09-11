inline void Print( FILE *fo, bool is_leaf ) const{
                if( !is_leaf ){
                    fprintf( fo, "gain=%f,cover=%f", loss_chg, sum_hess );
                }else{
                    fprintf( fo, "cover=%f", sum_hess );
                }
            }
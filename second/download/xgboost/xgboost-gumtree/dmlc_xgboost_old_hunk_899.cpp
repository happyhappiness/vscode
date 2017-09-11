            }
            inline void TaskTest( void ){
                std::vector<float> preds;
                learner.Predict( preds, data );
                FILE *fo = utils::FopenCheck( name_pred.c_str(), "w" );
                for( size_t i = 0; i < preds.size(); i ++ ){
                    fprintf( fo, "%f\n", preds[i] );

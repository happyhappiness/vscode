inline void Eval( FILE *fo, const char *evname,
                              const std::vector<float> &preds, 
                              const std::vector<float> &labels ){
                const float loss = mparam.Loss( preds, labels );
                fprintf( fo, "\t%s:%f", evname, loss );
            }
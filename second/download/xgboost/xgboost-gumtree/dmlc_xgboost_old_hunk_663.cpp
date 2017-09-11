                    if( rec[i].first != rec[i+1].first ){
                        double ams = sqrtf( 2*((s_tp+b_fp+br) * log( 1.0 + s_tp/(b_fp+br) ) - s_tp) );
                        if( tams < ams ){
                            threshold = (rec[i].first + rec[i+1].first) / 2.0;
                            tams = ams;
                        }
                    }
                }
                fprintf( stderr, "\tams-thres=%g", threshold );
                return tams;
            }
            virtual const char *Name(void) const{
                return "ams";
            }
            double wtarget;
        };

        /*! \brief Error */

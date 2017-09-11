                    if( rec[i].first != rec[i+1].first ){
                        double ams = sqrtf( 2*((s_tp+b_fp+br) * log( 1.0 + s_tp/(b_fp+br) ) - s_tp) );
                        if( tams < ams ){
                            thresindex = i;
                            tams = ams;
                        }
                    }
                }
                if( ntop == ndata ){
                    fprintf( stderr, "\tams-ratio=%g", float(thresindex)/ndata );
                    return tams;
                }else{
                    return sqrtf( 2*((s_tp+b_fp+br) * log( 1.0 + s_tp/(b_fp+br) ) - s_tp) );
                }
            }
            virtual const char *Name(void) const{
                return name_.c_str();
            }
        private:
            std::string name_;
            float ratio_;
        };

        /*! \brief Error */

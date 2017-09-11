        * \param val  value of the parameter
        */
        inline void SetParam( const char *name, const char *val ) {
            if( !strcmp("loss_type", name ) )   loss_type = atoi( val );
            if( !strcmp("bst:num_feature", name ) ) num_feature = atoi( val );
	    if( !strcmp("rank:sampler",name)) sampler = atoi( val );
        }


        /*!
        * \brief calculate first order gradient of pairwise loss function(f(x) = ln(1+exp(-x)), 

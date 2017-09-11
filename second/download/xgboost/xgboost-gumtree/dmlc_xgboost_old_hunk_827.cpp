        * \param val  value of the parameter
        */
        inline void SetParam( const char *name, const char *val ) {
            if( !strcmp("base_score", name ) )  base_score = (float)atof( val );
            if( !strcmp("loss_type", name ) )   loss_type = atoi( val );
            if( !strcmp("bst:num_feature", name ) ) num_feature = atoi( val );
        }
        /*!
        * \brief adjust base_score
        */
        inline void AdjustBase( void ) {
            if( loss_type == 1 || loss_type == 2 ) {
                utils::Assert( base_score > 0.0f && base_score < 1.0f, "sigmoid range constrain" );
                base_score = - logf( 1.0f / base_score - 1.0f );
            }
        }

        /*!
        * \brief transform the linear sum to prediction
        * \param x linear sum of boosting ensemble
        * \return transformed prediction
        */
        inline float PredTransform( float x ) {
            switch( loss_type ) {
            case PAIRWISE:
            case MAP:
            case NDCG:
                return 1.0f/(1.0f + expf(-x));
            default:
                utils::Error("unknown loss_type");
                return 0.0f;
            }
        }

        /*!
        * \brief calculate first order gradient of pairwise loss function(f(x) = ln(1+exp(-x)), 

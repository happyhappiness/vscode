            std::vector<Type>        types_;
        };
    }; // namespace utils

    namespace utils{
        /*! \brief feature constraint, allow or disallow some feature during training */
        class FeatConstrain{
        public:
            FeatConstrain( void ){
                default_state_ = +1;
            }
            /*!\brief set parameters */
            inline void SetParam( const char *name, const char *val ){
                int a, b;
                if( !strcmp( name, "fban") ){
                    this->ParseRange( val, a, b );
                    this->SetRange( a, b, -1 );
                }
                if( !strcmp( name, "fpass") ){
                    this->ParseRange( val, a, b );
                    this->SetRange( a, b, +1 );
                }
                if( !strcmp( name, "fdefault") ){
                    default_state_ = atoi( val );
                }
            }
            /*! \brief whether constrain is specified */
            inline bool HasConstrain( void ) const {
                return state_.size() != 0 && default_state_ == 1;
            }
            /*! \brief whether a feature index is banned or not */
            inline bool NotBanned( unsigned index ) const{
                int rt = index < state_.size() ? state_[index] : default_state_;
                if( rt == 0 ) rt = default_state_;
                return rt == 1;
            }
        private:
            inline void SetRange( int a, int b, int st ){
                if( b > (int)state_.size() ) state_.resize( b, 0 );
                for( int i = a; i < b; ++ i ){
                    state_[i] = st;
                }  
            }
            inline void ParseRange( const char *val, int &a, int &b ){
                if( sscanf( val, "%d-%d", &a, &b ) == 2 ) return;
                utils::Assert( sscanf( val, "%d", &a ) == 1 );
                b = a + 1;
            }
            /*! \brief default state */
            int default_state_;
            /*! \brief whether the state here is, +1:pass, -1: ban, 0:default */
            std::vector<int> state_;            
        };
    }; // namespace utils
}; // namespace xgboost
#endif // XGBOOST_FMAP_H

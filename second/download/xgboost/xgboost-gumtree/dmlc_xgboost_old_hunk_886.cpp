        const bool bst_debug = false;    
    };
};
namespace xgboost{
    namespace booster{
        /*! 
         * \brief feature matrix to store training instance, in sparse CSR format
         */
        class FMatrixS{
        public:
            /*! \brief one row of sparse feature matrix */
            struct Line{
                /*! \brief array of feature index */
                const bst_uint  *findex;
                /*! \brief array of feature value */
                const bst_float *fvalue;
                /*! \brief size of the data */
                bst_uint len;
            };
            /*! 
             * \brief remapped image of sparse matrix, 
             *  allows use a subset of sparse matrix, by specifying a rowmap
             */
            struct Image{
            public:
                Image( const FMatrixS &smat ):smat(smat), row_map( tmp_rowmap ){                
                }
                Image( const FMatrixS &smat, const std::vector<unsigned> &row_map )
                    :smat(smat), row_map(row_map){
                }
                /*! \brief get sparse part of current row */
                inline Line operator[]( size_t sidx ) const{
                    if( row_map.size() == 0 ) return smat[ sidx ];
                    else return smat[ row_map[ sidx ] ];
                }
            private:
                // used to set the simple case
                std::vector<unsigned> tmp_rowmap;
                const FMatrixS &smat;
                const std::vector<unsigned> &row_map;
            };
        public:
            // -----Note: unless needed for hacking, these fields should not be accessed directly -----
            /*! \brief row pointer of CSR sparse storage */
            std::vector<size_t>  row_ptr;
            /*! \brief index of CSR format */
            std::vector<bst_uint>   findex;
            /*! \brief value of CSR format */
            std::vector<bst_float>  fvalue;
        public:
            /*! \brief constructor */
            FMatrixS( void ){ this->Clear(); }
            /*! 
             * \brief get number of rows 
             * \return number of rows
             */
            inline size_t NumRow( void ) const{
                return row_ptr.size() - 1;
            }
            /*! 
             * \brief get number of nonzero entries
             * \return number of nonzero entries
             */
            inline size_t NumEntry( void ) const{
                return findex.size();
            }
            /*! \brief clear the storage */
            inline void Clear( void ){
                row_ptr.resize( 0 );
                findex.resize( 0 );
                fvalue.resize( 0 );
                row_ptr.push_back( 0 );
            }
            /*! 
             * \brief add a row to the matrix, but only accept features from fstart to fend
             *  \param feat sparse feature
             *  \param fstart start bound of feature
             *  \param fend   end bound range of feature
             *  \return the row id of added line
             */
            inline size_t AddRow( const Line &feat, unsigned fstart = 0, unsigned fend = UINT_MAX ){
                utils::Assert( feat.len >= 0, "sparse feature length can not be negative" );
                unsigned cnt = 0;
                for( unsigned i = 0; i < feat.len; i ++ ){
                    if( feat.findex[i] < fstart || feat.findex[i] >= fend ) continue;
                    findex.push_back( feat.findex[i] );
                    fvalue.push_back( feat.fvalue[i] );
                    cnt ++;
                }
                row_ptr.push_back( row_ptr.back() + cnt );
                return row_ptr.size() - 2;
            }

            /*! 
             * \brief add a row to the matrix, with data stored in STL container
             * \param findex feature index
             * \param fvalue feature value
             * \return the row id added line
             */
            inline size_t AddRow( const std::vector<bst_uint> &findex, 
                                  const std::vector<bst_float> &fvalue ){
                FMatrixS::Line l;
                utils::Assert( findex.size() == fvalue.size() );
                l.findex = &findex[0];
                l.fvalue = &fvalue[0];
                l.len = static_cast<bst_uint>( findex.size() );
                return this->AddRow( l );
            }
            /*! \brief get sparse part of current row */
            inline Line operator[]( size_t sidx ) const{
                Line sp;
                utils::Assert( !bst_debug || sidx < this->NumRow(), "row id exceed bound" );
                sp.len = static_cast<bst_uint>( row_ptr[ sidx + 1 ] - row_ptr[ sidx ] );
                sp.findex = &findex[ row_ptr[ sidx ] ];
                sp.fvalue = &fvalue[ row_ptr[ sidx ] ];
                return sp;
            }
        public:
            /*!

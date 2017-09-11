        const bool bst_debug = false;    
    };
};

namespace xgboost{
    namespace booster{
        /**
         * \brief This is a interface, defining the way to access features, 
         *        by column or by row. This interface is used to make implementation
         *        of booster does not depend on how feature is stored.
         *
         *        Why template instead of virtual class: for efficiency
         *          feature matrix is going to be used by most inner loop of the algorithm
         *
         * \tparam Derived type of actual implementation 
         * \sa FMatrixS: most of time FMatrixS is sufficient, refer to it if you find it confusing
         */
        template<typename Derived>
        struct FMatrix{
        public:
            /*! \brief exmaple iterator over one row */            
            struct RowIter{
                /*! 
                 * \brief move to next position 
                 * \return whether there is element in next position
                 */
                inline bool Next( void );
                /*! \return feature index in current position */
                inline bst_uint  findex( void ) const;
                /*! \return feature value in current position */
                inline bst_float fvalue( void ) const;
            };
            /*! \brief example iterator over one column */
            struct ColIter{
                /*! 
                 * \brief move to next position 
                 * \return whether there is element in next position
                 */
                inline bool Next( void );
                /*! \return row index of current position  */
                inline bst_uint  rindex( void ) const;
                /*! \return feature value in current position */
                inline bst_float fvalue( void ) const;
            };
        public:
            /*! 
             * \brief prepare sorted columns so that GetSortedCol can be called
             */
            inline void MakeSortedCol( void );
            /*! 
             * \brief get number of rows 
             * \return number of rows
             */
            inline size_t NumRow( void ) const;
            /*! 
             * \brief get number of columns
             * \return number of columns
             */
            inline size_t NumCol( void ) const;
            /*!
             * \brief get row iterator
             * \param ridx row index
             * \return row iterator
             */
            inline RowIter GetRow( size_t ridx ) const;
            /*!
             * \brief get column iterator, the columns must be sorted by feature value
             * \param ridx column index
             * \return column iterator
             */
            inline ColIter GetSortedCol( size_t ridx ) const;

            /*! \return the view of derived class */
            inline const Derived& self( void ) const{
                return *static_cast<const Derived*>(this);
            }
        };
    };
};

namespace xgboost{
    namespace booster{
        /*! 
         * \brief feature matrix to store training instance, in sparse CSR format
         */        
        class FMatrixS: public FMatrix<FMatrixS>{
        public:
            /*! \brief one entry in a row */
            struct REntry{
                /*! \brief feature index */
                bst_uint  findex;
                /*! \brief feature value */
                bst_float fvalue;
            };
            /*! \brief one entry in a row */
            struct CEntry{
                /*! \brief row index */
                bst_uint  rindex;
                /*! \brief feature value */
                bst_float fvalue;
            };
            /*! \brief one row of sparse feature matrix */
            struct Line{
                /*! \brief array of feature index */
                const REntry *data_;
                /*! \brief size of the data */
                bst_uint len;
                inline const REntry& operator[]( unsigned i ) const{
                    return data_[i];
                }  
            };
        public:
            struct RowIter{
                const REntry *dptr, *end;                
                inline bool Next( void ){
                    if( dptr == end ) return false;
                    else{
                       ++ dptr; return true;
                    }
                }
                inline bst_uint  findex( void ) const{
                    return dptr->findex;
                }
                inline bst_float fvalue( void ) const{
                    return dptr->fvalue;
                }                
            };
        public:
            /*! \brief constructor */
            FMatrixS( void ){ this->Clear(); }
            /*!  \brief get number of rows */
            inline size_t NumRow( void ) const{
                return row_ptr_.size() - 1;
            }
            /*! 
             * \brief get number of nonzero entries
             * \return number of nonzero entries
             */
            inline size_t NumEntry( void ) const{
                return row_data_.size();
            }
            /*! \brief clear the storage */
            inline void Clear( void ){
                row_ptr_.clear();
                row_ptr_.push_back( 0 );
                row_data_.clear();
            }
            /*! \brief get sparse part of current row */
            inline Line operator[]( size_t sidx ) const{
                Line sp;
                utils::Assert( !bst_debug || sidx < this->NumRow(), "row id exceed bound" );
                sp.len = static_cast<bst_uint>( row_ptr_[ sidx + 1 ] - row_ptr_[ sidx ] );
                sp.data_ = &row_data_[ row_ptr_[ sidx ] ];
                return sp;
            }            
            /*!  \brief get row iterator*/
            inline RowIter GetRow( size_t ridx ) const{
                utils::Assert( !bst_debug || ridx < this->NumRow(), "row id exceed bound" );
                RowIter it; 
                it.dptr = &row_data_[ row_ptr_[ridx] ] - 1;
                it.dptr = &row_data_[ row_ptr_[ridx+1] ] - 1;
                return it;
            }
            /*! 
             * \brief add a row to the matrix, with data stored in STL container
             * \param findex feature index
             * \param fvalue feature value
             *  \param fstart start bound of feature
             *  \param fend   end bound range of feature
             * \return the row id added line
             */
            inline size_t AddRow( const std::vector<bst_uint> &findex, 
                                  const std::vector<bst_float> &fvalue,
                                  unsigned fstart = 0, unsigned fend = UINT_MAX ){
                utils::Assert( findex.size() == fvalue.size() );
                unsigned cnt = 0;
                for( size_t i = 0; i < findex.size(); i ++ ){
                    if( findex[i] < fstart || findex[i] >= fend ) continue;
                    REntry e; e.findex = findex[i]; e.fvalue = fvalue[i];
                    row_data_.push_back( e );
                    cnt ++;
                }
                row_ptr_.push_back( row_ptr_.back() + cnt );
                return row_ptr_.size() - 2;
            }
        public:
            /*!

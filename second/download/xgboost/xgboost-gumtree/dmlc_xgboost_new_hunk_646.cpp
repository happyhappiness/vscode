namespace xgboost{
    namespace regrank{        
       inline IObjFunction* CreateObjFunction( const char *name ){
           if( !strcmp("reg:linear", name ) )     return new RegressionObj( LossType::kLinearSquare );
           if( !strcmp("reg:logistic", name ) )    return new RegressionObj( LossType::kLogisticNeglik );
           if( !strcmp("binary:logistic", name ) ) return new RegressionObj( LossType::kLogisticClassify );

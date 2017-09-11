@@ -346,16 +346,30 @@ namespace xgboost{
                     const unsigned split_index = nodes[ nid ].split_index();
 
                     if( split_index < fmap.size() ){
-                        if( fmap.type(split_index) == utils::FeatMap::kIndicator ){
+                        switch( fmap.type(split_index) ){
+                        case utils::FeatMap::kIndicator:{
                             int nyes = nodes[ nid ].default_left()?nodes[nid].cright():nodes[nid].cleft();
                             fprintf( fo, "%d:[%s] yes=%d,no=%d", 
                                      nid, fmap.name( split_index ),
-                                     nyes, nodes[nid].cdefault() );                            
-                        }else{
+                                     nyes, nodes[nid].cdefault() );
+                            break;                            
+                        }
+                        case utils::FeatMap::kInteger:{
+                            fprintf( fo, "%d:[%s<%d] yes=%d,no=%d,missing=%d", 
+                                     nid, fmap.name(split_index), int( float(cond)+1.0f), 
+                                     nodes[ nid ].cleft(), nodes[ nid ].cright(),
+                                     nodes[ nid ].cdefault() );
+                            break;
+                        }
+                        case utils::FeatMap::kFloat:
+                        case utils::FeatMap::kQuantitive:{
                             fprintf( fo, "%d:[%s<%f] yes=%d,no=%d,missing=%d", 
                                      nid, fmap.name(split_index), float(cond), 
                                      nodes[ nid ].cleft(), nodes[ nid ].cright(),
                                      nodes[ nid ].cdefault() );
+                            break;
+                        }
+                        default: utils::Error("unknown fmap type");
                         }
                     }else{
                         fprintf( fo, "%d:[f%u<%f] yes=%d,no=%d,missing=%d", 
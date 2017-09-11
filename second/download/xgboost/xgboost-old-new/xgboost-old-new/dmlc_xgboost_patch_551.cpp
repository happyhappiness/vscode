@@ -16,9 +16,9 @@
 
 namespace xgboost{
 	namespace booster{
-		/*��
-		* \brief listing the types of boosters
-		*/
+		/*
+         * \brief listing the types of boosters
+         */
 		enum BOOSTER_TYPE_LIST{
 			TREE,
 			LINEAR,
@@ -30,8 +30,8 @@ namespace xgboost{
 		*/
 		IBooster *CreateBooster( int booster_type ){
 			switch( booster_type ){
-			case TREE: return new RTreeTrainer();
-			case LINEAR: return new LinearBooster();
+            case TREE: return new RTreeTrainer();
+            case LINEAR: return new LinearBooster();
 			default: utils::Error("unknown booster_type"); return NULL;
 			}
 		}
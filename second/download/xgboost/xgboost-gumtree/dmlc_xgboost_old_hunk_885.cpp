		*/
		IBooster *CreateBooster( int booster_type ){
			switch( booster_type ){
			case TREE: return new RTreeTrainer();
			case LINEAR: return new LinearBooster();
			default: utils::Error("unknown booster_type"); return NULL;
			}
		}

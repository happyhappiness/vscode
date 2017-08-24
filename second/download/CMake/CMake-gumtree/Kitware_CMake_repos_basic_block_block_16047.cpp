{
		case DIR_REC_VD:
			/* This case does not come, but compiler
			 * complains that DIR_REC_VD not handled
			 *  in switch ....  */
			break;
		case DIR_REC_SELF:
			isoent->dr_len.self = (int)dr_len; break;
		case DIR_REC_PARENT:
			isoent->dr_len.parent = (int)dr_len; break;
		case DIR_REC_NORMAL:
			isoent->dr_len.normal = (int)dr_len; break;
		}
{
		case DIR_REC_VD:
		case DIR_REC_SELF:
			set_num_711(bp+34, 0);
			break;
		case DIR_REC_PARENT:
			set_num_711(bp+34, 1);
			break;
		case DIR_REC_NORMAL:
			if (isoent->identifier != NULL)
				memcpy(bp+34, isoent->identifier, fi_len);
			else
				set_num_711(bp+34, 0);
			break;
		}
(p != NULL)
			/* Length of Directory Record */
			set_num_711(p, (unsigned char)dr_len);
		else
			isoent->dr_len.vd = (int)dr_len
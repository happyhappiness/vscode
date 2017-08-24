{
				++val;
				ns = (long)mtree_atol10(&val);
				if (ns < 0)
					ns = 0;
				else if (ns > 999999999)
					ns = 999999999;
			}
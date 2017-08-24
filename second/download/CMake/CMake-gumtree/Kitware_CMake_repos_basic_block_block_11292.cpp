{
				br->odd = *strm->next_in++;
				strm->avail_in--;
				br->have_odd = 1;
			}
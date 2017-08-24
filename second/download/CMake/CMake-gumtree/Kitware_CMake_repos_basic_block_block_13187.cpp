{
			if (avail_out > avail_in)
				avail_out = avail_in;
			memcpy(outbuff, b, avail_out);
			*used = avail_out;
			*outbytes = avail_out;
		}
(dicsize <= 0x03F00000 && dicsize >= 0x00300000 &&
		    (dicsize & ((1 << 20)-1)) == 0 &&
		    bits_checked == 8 + 64) {
			bits_checked += 32;
			break;
		}
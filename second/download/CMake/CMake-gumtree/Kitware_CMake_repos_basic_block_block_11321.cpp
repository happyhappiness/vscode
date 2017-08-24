(i = 0; i < ds->at.len_size; i++) {
				ds->at.bitlen[i] = lzx_br_bits(br, 3);
				ds->at.freq[ds->at.bitlen[i]]++;
				lzx_br_consume(br, 3);
			}
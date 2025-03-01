{
		case 17:/* several zero lengths, from 4 to 19. */
			if (!lzx_br_read_ahead(strm, br, ds->pt.bitlen[c]+4))
				goto getdata;
			lzx_br_consume(br, ds->pt.bitlen[c]);
			same = lzx_br_bits(br, 4) + 4;
			if (i + same > end)
				return (-1);/* Invalid */
			lzx_br_consume(br, 4);
			for (j = 0; j < same; j++)
				d->bitlen[i++] = 0;
			break;
		case 18:/* many zero lengths, from 20 to 51. */
			if (!lzx_br_read_ahead(strm, br, ds->pt.bitlen[c]+5))
				goto getdata;
			lzx_br_consume(br, ds->pt.bitlen[c]);
			same = lzx_br_bits(br, 5) + 20;
			if (i + same > end)
				return (-1);/* Invalid */
			lzx_br_consume(br, 5);
			memset(d->bitlen + i, 0, same);
			i += same;
			break;
		case 19:/* a few same lengths. */
			if (!lzx_br_read_ahead(strm, br,
			    ds->pt.bitlen[c]+1+ds->pt.max_bits))
				goto getdata;
			lzx_br_consume(br, ds->pt.bitlen[c]);
			same = lzx_br_bits(br, 1) + 4;
			if (i + same > end)
				return (-1);
			lzx_br_consume(br, 1);
			rbits = lzx_br_bits(br, ds->pt.max_bits);
			c = lzx_decode_huffman(&(ds->pt), rbits);
			lzx_br_consume(br, ds->pt.bitlen[c]);
			c = (d->bitlen[i] - c + 17) % 17;
			if (c < 0)
				return (-1);/* Invalid */
			for (j = 0; j < same; j++)
				d->bitlen[i++] = c;
			d->freq[c] += same;
			break;
		default:
			lzx_br_consume(br, ds->pt.bitlen[c]);
			c = (d->bitlen[i] - c + 17) % 17;
			if (c < 0)
				return (-1);/* Invalid */
			d->freq[c]++;
			d->bitlen[i++] = c;
			break;
		}
((nx = parse(&ucx[0], s, len))
				    > 0) {
					cx = CCC(ucx[0]);
					if (cl > cx)
						break;
					s += nx;
					len -= nx;
					cl = cx;
					UNPARSE(p, endp, ucx[0]);
				}
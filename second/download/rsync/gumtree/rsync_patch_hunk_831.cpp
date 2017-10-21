 			diag = left;
 		}
 	}
 
 	return a[len2-1];
 }
+
+#define BB_SLOT_SIZE     (16*1024)          /* Desired size in bytes */
+#define BB_PER_SLOT_BITS (BB_SLOT_SIZE * 8) /* Number of bits per slot */
+#define BB_PER_SLOT_INTS (BB_SLOT_SIZE / 4) /* Number of int32s per slot */
+
+struct bitbag {
+    uint32 **bits;
+    int slot_cnt;
+};
+
+struct bitbag *bitbag_create(int max_ndx)
+{
+	struct bitbag *bb = new(struct bitbag);
+	bb->slot_cnt = (max_ndx + BB_PER_SLOT_BITS - 1) / BB_PER_SLOT_BITS;
+
+	if (!(bb->bits = (uint32**)calloc(bb->slot_cnt, sizeof (uint32*))))
+		out_of_memory("bitbag_create");
+
+	return bb;
+}
+
+void bitbag_set_bit(struct bitbag *bb, int ndx)
+{
+	int slot = ndx / BB_PER_SLOT_BITS;
+	ndx %= BB_PER_SLOT_BITS;
+
+	if (!bb->bits[slot]) {
+		if (!(bb->bits[slot] = (uint32*)calloc(BB_PER_SLOT_INTS, 4)))
+			out_of_memory("bitbag_set_bit");
+	}
+
+	bb->bits[slot][ndx/32] |= 1u << (ndx % 32);
+}
+
+#if 0 /* not needed yet */
+void bitbag_clear_bit(struct bitbag *bb, int ndx)
+{
+	int slot = ndx / BB_PER_SLOT_BITS;
+	ndx %= BB_PER_SLOT_BITS;
+
+	if (!bb->bits[slot])
+		return;
+
+	bb->bits[slot][ndx/32] &= ~(1u << (ndx % 32));
+}
+
+int bitbag_check_bit(struct bitbag *bb, int ndx)
+{
+	int slot = ndx / BB_PER_SLOT_BITS;
+	ndx %= BB_PER_SLOT_BITS;
+
+	if (!bb->bits[slot])
+		return 0;
+
+	return bb->bits[slot][ndx/32] & (1u << (ndx % 32)) ? 1 : 0;
+}
+#endif
+
+/* Call this with -1 to start checking from 0.  Returns -1 at the end. */
+int bitbag_next_bit(struct bitbag *bb, int after)
+{
+	uint32 bits, mask;
+	int i, ndx = after + 1;
+	int slot = ndx / BB_PER_SLOT_BITS;
+	ndx %= BB_PER_SLOT_BITS;
+
+	mask = (1u << (ndx % 32)) - 1;
+	for (i = ndx / 32; slot < bb->slot_cnt; slot++, i = mask = 0) {
+		if (!bb->bits[slot])
+			continue;
+		for ( ; i < BB_PER_SLOT_INTS; i++, mask = 0) {
+			if (!(bits = bb->bits[slot][i] & ~mask))
+				continue;
+			/* The xor magic figures out the lowest enabled bit in
+			 * bits, and the switch quickly computes log2(bit). */
+			switch (bits ^ (bits & (bits-1))) {
+#define LOG2(n) case 1u << n: return slot*BB_PER_SLOT_BITS + i*32 + n
+			    LOG2(0);  LOG2(1);  LOG2(2);  LOG2(3);
+			    LOG2(4);  LOG2(5);  LOG2(6);  LOG2(7);
+			    LOG2(8);  LOG2(9);  LOG2(10); LOG2(11);
+			    LOG2(12); LOG2(13); LOG2(14); LOG2(15);
+			    LOG2(16); LOG2(17); LOG2(18); LOG2(19);
+			    LOG2(20); LOG2(21); LOG2(22); LOG2(23);
+			    LOG2(24); LOG2(25); LOG2(26); LOG2(27);
+			    LOG2(28); LOG2(29); LOG2(30); LOG2(31);
+			}
+			return -1; /* impossible... */
+		}
+	}
+
+	return -1;
+}

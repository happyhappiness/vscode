
int expand_ref(const char *str, int len, unsigned char *sha1, char **ref);
int dwim_ref(const char *str, int len, unsigned char *sha1, char **ref);
int dwim_log(const char *str, int len, unsigned char *sha1, char **ref);

/*
 * A ref_transaction represents a collection of reference updates that
 * should succeed or fail together.
 *
 * Calling sequence
 * ----------------
 *
 * - Allocate and initialize a `struct ref_transaction` by calling
 *   `ref_transaction_begin()`.
 *
 * - Specify the intended ref updates by calling one or more of the
 *   following functions:
 *   - `ref_transaction_update()`
 *   - `ref_transaction_create()`
 *   - `ref_transaction_delete()`
 *   - `ref_transaction_verify()`
 *
 * - Then either:
 *
 *   - Optionally call `ref_transaction_prepare()` to prepare the
 *     transaction. This locks all references, checks preconditions,
 *     etc. but doesn't finalize anything. If this step fails, the
 *     transaction has been closed and can only be freed. If this step
 *     succeeds, then `ref_transaction_commit()` is almost certain to
 *     succeed. However, you can still call `ref_transaction_abort()`
 *     if you decide not to commit the transaction after all.
 *
 *   - Call `ref_transaction_commit()` to execute the transaction,
 *     make the changes permanent, and release all locks. If you
 *     haven't already called `ref_transaction_prepare()`, then
 *     `ref_transaction_commit()` calls it for you.
 *
 *   Or
 *
 *   - Call `initial_ref_transaction_commit()` if the ref database is
 *     known to be empty and have no other writers (e.g. during
 *     clone). This is likely to be much faster than
 *     `ref_transaction_commit()`. `ref_transaction_prepare()` should
 *     *not* be called before `initial_ref_transaction_commit()`.
 *
 * - Then finally, call `ref_transaction_free()` to free the
 *   `ref_transaction` data structure.
 *
 * At any time before calling `ref_transaction_commit()`, you can call
 * `ref_transaction_abort()` to abort the transaction, rollback any
 * locks, and free any associated resources (including the
 * `ref_transaction` data structure).
 *
 * Putting it all together, a complete reference update looks like
 *
 *         struct ref_transaction *transaction;
 *         struct strbuf err = STRBUF_INIT;
 *         int ret = 0;
 *
 *         transaction = ref_store_transaction_begin(refs, &err);
 *         if (!transaction ||
 *             ref_transaction_update(...) ||
 *             ref_transaction_create(...) ||
 *             ...etc... ||
 *             ref_transaction_commit(transaction, &err)) {
 *                 error("%s", err.buf);
 *                 ret = -1;
 *         }
 *         ref_transaction_free(transaction);
 *         strbuf_release(&err);
 *         return ret;
 *
 * Error handling
 * --------------
 *
 * On error, transaction functions append a message about what
 * went wrong to the 'err' argument.  The message mentions what

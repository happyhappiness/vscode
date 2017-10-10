 */
#ifndef FLEX_ARRAY
# define FLEX_ARRAY 1
#endif
#endif


/*
 * BUILD_ASSERT_OR_ZERO - assert a build-time dependency, as an expression.
 * @cond: the compile-time condition which must be true.
 *
 * Your compile will fail if the condition isn't true, or can't be evaluated
 * by the compiler.  This can be used in an expression: its value is "0".
 *
 * Example:
 *	#define foo_to_char(foo)					\
 *		 ((char *)(foo)						\
 *		  + BUILD_ASSERT_OR_ZERO(offsetof(struct foo, string) == 0))
 */
#define BUILD_ASSERT_OR_ZERO(cond) \
	(sizeof(char [1 - 2*!(cond)]) - 1)

#if defined(__GNUC__) && (__GNUC__ >= 3)
# if GIT_GNUC_PREREQ(3, 1)
 /* &arr[0] degrades to a pointer: a different type from an array */
# define BARF_UNLESS_AN_ARRAY(arr)						\
	BUILD_ASSERT_OR_ZERO(!__builtin_types_compatible_p(__typeof__(arr), \
							   __typeof__(&(arr)[0])))
# else
#  define BARF_UNLESS_AN_ARRAY(arr) 0
# endif
#endif
/*
 * ARRAY_SIZE - get the number of elements in a visible array
 *  <at> x: the array whose size you want.
 *
 * This does not work on pointers, or arrays declared as [], or
 * function parameters.  With correct compiler support, such usage
 * will cause a build error (see the build_assert_or_zero macro).
 */
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]) + BARF_UNLESS_AN_ARRAY(x))

#define bitsizeof(x)  (CHAR_BIT * sizeof(x))

#define maximum_signed_value_of_type(a) \
    (INTMAX_MAX >> (bitsizeof(intmax_t) - bitsizeof(a)))

#define maximum_unsigned_value_of_type(a) \

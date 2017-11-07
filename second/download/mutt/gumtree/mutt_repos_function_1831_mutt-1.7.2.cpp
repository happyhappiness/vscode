static inline struct expression *
new_exp_0 (op)
     enum operator op;
{
  return new_exp (0, op, NULL);
}
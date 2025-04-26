/*
 * test_push_swap.c – lightweight smoke-tests (no Criterion)
 * --------------------------------------------------------
 * Build:
 *     cc -Wall -Wextra -Werror -o unit_tests *.c test_push_swap.c -lft
 *
 * Run:
 *     ./unit_tests
 *
 * The harness prints a ✓/❌ result for each test and aborts on the first
 * failure.  It does **not** call any file-scope `static` functions directly –
 * everything is exercised through the public API defined in push_swap.h.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "push_swap.h"
 
 /* ────────────────────────────  macros  ──────────────────────────── */
 
 /*
  * FAILF – print a formatted error and abort.
  * The `##__VA_ARGS__` trick allows calls without extra parameters.
  */
 #define FAILF(fmt, ...)                                                                 \
	 do {                                                                                \
		 fprintf(stderr, "\n❌  " fmt "\n", ##__VA_ARGS__);                              \
		 exit(EXIT_FAILURE);                                                             \
	 } while (0)
 
 #define CHECK_INT_EQ(expected, actual, ctx)                                             \
	 do {                                                                                \
		 if ((expected) != (actual))                                                     \
			 FAILF("%s – expected %d, got %d", (ctx), (int)(expected), (int)(actual));  \
	 } while (0)
 
 /* ─────────────────────────── helpers  ──────────────────────────── */
 
 static t_stack_element *new_elem(int nb)
 {
	 t_stack_element *e = malloc(sizeof(*e));
	 if (!e) {
		 perror("malloc");
		 exit(EXIT_FAILURE);
	 }
	 e->nb     = nb;
	 e->next   = NULL;
	 e->former = NULL;
	 return e;
 }
 
 static void init_stack(t_stack *s)
 {
	 s->head         = NULL;
	 s->stack_length = 0;
 }
 
 /* Copies up to `cap` elements into `out`; returns how many were copied. */
 static int stack_to_array(t_stack *s, int *out, size_t cap)
 {
	 if (!s->head)
		 return 0;
 
	 t_stack_element *cur = s->head;
	 size_t i = 0;
 
	 do {
		 if (i >= cap)
			 break;
		 out[i++] = cur->nb;
		 cur = cur->next;
	 } while (cur != s->head);
 
	 return (int)i;
 }
 
 static void free_circle(t_stack *s)
 {
	 if (!s->head)
		 return;
 
	 unsigned int left = s->stack_length;
	 t_stack_element *cur = s->head;
	 while (left--) {
		 t_stack_element *next = cur->next;
		 free(cur);
		 cur = next;
	 }
 }
 
 /* ─────────────────────────── tests  ─────────────────────────── */
 
 static void test_stack_primitives(void)
 {
	 puts("• stack_add_element / stack_fetch");
 
	 t_stack s; init_stack(&s);
	 t_stack_element *a = new_elem(1);
	 t_stack_element *b = new_elem(2);
 
	 stack_add_element(a, &s);
	 stack_add_element(b, &s);   /* b becomes new head */
 
	 CHECK_INT_EQ(2, s.stack_length, "length after 2 pushes");
	 CHECK_INT_EQ(2, s.head->nb,     "head value");
 
	 t_stack_element *popped = stack_fetch(&s);
	 CHECK_INT_EQ(2, popped->nb,     "popped value");
	 CHECK_INT_EQ(1, s.stack_length, "length after pop");
 
	 free(a);
	 free(b);
	 puts("  ✓ passed");
 }
 
 static void test_sa(void)
 {
	 puts("• sa swap");
 
	 t_stack s; init_stack(&s);
	 stack_add_element(new_elem(1), &s);
	 stack_add_element(new_elem(2), &s);   /* head = 2 */
 
	 char *ops = malloc(1);
	 *ops = 0;
	 if (sa(ops, &s) != 0)
		 FAILF("sa returned error code");
 
	 int seq[2];
	 stack_to_array(&s, seq, 2);
	 CHECK_INT_EQ(1, seq[0], "top after sa");
	 CHECK_INT_EQ(2, seq[1], "second after sa");
 
	 //free(ops);
	 free_circle(&s);
	 puts("  ✓ passed");
 }
 
 static void test_rotate(void)
 {
	 puts("• ra / rra rotation");
 
	 t_stack s; init_stack(&s);
	 stack_add_element(new_elem(1), &s);
	 stack_add_element(new_elem(2), &s);
	 stack_add_element(new_elem(3), &s);  /* head = 3 */
 
	 char *ops = ft_strdup("");
 
	 ra(ops, &s);   /* expect order: 2(top), 1, 3 */
	 CHECK_INT_EQ(2, s.head->nb, "head after ra");
 
	 rra(ops, &s);  /* back to 3(top), 2, 1 */
	 CHECK_INT_EQ(3, s.head->nb, "head after rra");
 
	 //free(ops);
	 free_circle(&s);
	 puts("  ✓ passed");
 }
 
 static void test_build_stacks(void)
 {
	 puts("• build_stacks");
 
	 int nums[] = { 10, 20, 30 };
	 t_stack *a, *b;
 
	 if (build_stacks(&a, &b, nums, 3) != 0)
		 FAILF("build_stacks returned error");
 
	 CHECK_INT_EQ(3, (*a).stack_length, "stack A length");
	 CHECK_INT_EQ(0, (*b).stack_length, "stack B length");
 
	 int seq[3];
	 stack_to_array(a, seq, 3);
	 CHECK_INT_EQ(10, seq[0], "bottom of A");
	 CHECK_INT_EQ(20, seq[1], "middle of A");
	 CHECK_INT_EQ(30, seq[2], "top of A");
 
	 /* cleanup through burnit */
	 int *n = NULL; char *str = NULL;
	 burnit(&n, &str, &a, &b);
 
	 puts("  ✓ passed");
 }
 
 static void test_read_to_arr(void)
 {
	 puts("• read_to_arr");
 
	 char *argv_ok[]  = { "prog", "4", "3", "2", NULL };
	 int  *ok = read_to_arr(4, argv_ok);
	 if (!ok)
		 FAILF("read_to_arr returned NULL on valid input");
	 CHECK_INT_EQ(4, ok[0], "ok[1]");
	 CHECK_INT_EQ(3, ok[1], "ok[2]");
	 CHECK_INT_EQ(2, ok[2], "ok[3]");
	 free(ok);
 
	 char *argv_dup[] = { "p", "1", "2", "1", NULL };
	 int  *dup = read_to_arr(4, argv_dup);
	 if (dup)
		 FAILF("read_to_arr accepted duplicated numbers");
 
	 puts("  ✓ passed");
 }

 static void test_overflow_guard(void)
{
    puts("• overflow guard");

    char *argv_big[] = { "p", "2147483648", NULL };   /* INT_MAX + 1 */
    int  *big = read_to_arr(2, argv_big);
    if (big)
        FAILF("Overflow value accepted");
    puts("  ✓ passed");
}
 
 /* ─────────────────────────── main  ─────────────────────────── */
 
 int main(void)
 {
	 puts("Running push_swap smoke-tests…\n");
 
	 test_stack_primitives();
	 test_sa();
	 test_rotate();
	 test_build_stacks();
	 test_read_to_arr();
	 test_overflow_guard();
	 puts("\n✅  All checks passed.");
	 return EXIT_SUCCESS;
 }
 
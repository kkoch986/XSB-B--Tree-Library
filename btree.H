%:- compile_command 'make module'.

:- private_foreign_pred bt_init from cbt_init(void):int.
:- private_foreign_pred bt_close from cbt_close(void):int.

:- private_foreign_pred bt_insert(+t) from cbt_insert(t:term):int.
:- private_foreign_pred bt_get(+t, -retval) from cbt_get(t:term):term.

:- private_foreign_pred print_term(+t) from printTerm(t:term):void.
Thu Dec  9 10:51:19 1999  Mumit Khan  <khan@xraylith.wisc.edu>

	* lex.c (saving_parse_to_obstack): New global.
	(reinit_parse_for_block): Use.
	(reinit_parse_for_expr): Use.
	(check_newline): Use.

Tue Aug 17 12:04:14 1999  Mumit Khan  <khan@xraylith.wisc.edu>

	* g++spec.c (lang_specific_driver): Add room for NULL in arglist.

Mon Apr 26 12:25:41 1999 Donn Terry (donn@interix.com)

	* decl.c (xref_tag): Init TYPE_PACKED and TYPE_NATIVE from globals.
	* pt.c (instantiate_class_template): Propigate TYPE_NATIVE.

Sat Jun 26 11:51:20 1999  Mumit Khan  <khan@xraylith.wisc.edu>

	* decl.c (start_function): Disable Jason Merrill's change on
	1999-03-18 to suppress normal linkage heuristics for #pragma 
	interface under MULTIPLE_SYMBOL_SPACES.

Wed Jun  9 18:30:24 1999  Mumit Khan  <khan@xraylith.wisc.edu>

	* class.c (finish_base_struct): Allow multiple COM base classes
	as well as non-COM bases as long as it's not the leftmost.

1999-05-20  Jason Merrill  <jason@yorick.cygnus.com>

	* class.c (finish_struct_1): Still check for ANON_AGGR_TYPE_P.

	* class.c (finish_base_struct): Allow non-COM bases for COM classes
	except at the leftmost position.
	(modify_one_vtable, fixup_vtable_deltas1, override_one_vtable):
	Pass the binfo's class, not the most derived, to skip_rtti_stuff.
	* search.c (get_abstract_virtuals, expand_upcast_fixups): Likewise.

1999-05-19  Jason Merrill  <jason@yorick.cygnus.com>

	Implement anonymous structs.
	* cp-tree.h (ANON_AGGR_TYPE_P): Rename from ANON_UNION_TYPE_P.
	* class.c, decl.c, decl2.c, init.c, pt.c, search.c, typeck.c: Adjust.
	* class.c (finish_struct_1): Remove redundant check for anon struct.
	* decl.c (fixup_anonymous_aggr): Renamed from fixup_anonymous_union.
	(check_tag_decl): Check for anonymous struct here.
	* decl2.c (build_anon_union_vars): Catch anon struct at file scope.
	* init.c (sort_member_init, emit_base_init): Handle getting fields
	as well as names in current_member_init_list.
	(perform_member_init): Handle getting an anon aggr.
	* method.c (do_build_assign_ref): Don't descend into anon aggrs.
	(do_build_copy_constructor): Likewise.

1999-05-19  Jason Merrill  <jason@yorick.cygnus.com>

	* call.c (find_scoped_type, resolve_scope_to_name): Lose.
	* class.c (finish_struct_1): Use CLASS_TYPE_P.
	* ptree.c (print_lang_type): Likewise.
	* typeck.c (build_modify_expr, c_expand_asm_operands): Use
	IS_AGGR_TYPE_CODE.
	* typeck2.c (digest_init): Likewise.


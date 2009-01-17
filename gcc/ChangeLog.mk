2000-01-19  Mumit Khan  <khan@xraylith.wisc.edu>

	* i386/cygwin.h (CPP_SPEC): Update support for -mno-cygwin and
	-shared options.
	(LIB_SPEC): Likewise.
	(LINK_SPEC): Likewise.

	* protoize.c (SAVE_SUFFIX): Handle MSDOS/DJGPP filenames.
	(edit_file): Likewise. 
	(gen_aux_info_file): Use aux_info_suffix instead.
	* invoke.texi: Update documentation.

	* i386/winnt.c (i386_pe_unmark_dllimport): New static function.
	(i386_pe_encode_section_info): Use.
	(i386_pe_mark_dllimport): Likewise.
	(i386_pe_dllexport_p): Make static.
	(i386_pe_dllimport_p): Likewise.
	(i386_pe_mark_dllexport): Likewise. 
	(i386_pe_mark_dllimport): Likewise.
	(i386_pe_mark_dllexport): Implement override rules and handle 
	illegal dllimports/exports. 
	(i386_pe_mark_dllimport): Likewise. Don't import C++ methods
	and vtables.

	* protoize.c: Conditionally include unistd.h.
	(DIR_SEPARATOR): New macro.
	(IS_DIR_SEPARATOR): New macro.
	(IS_SAME_PATH_CHAR): New macro.
	(IS_SAME_PATH): New macro.
	(CPLUS_FILE_SUFFIX): New macro.
	(AUX_INFO_SUFFIX): New macro.
	(SAVE_SUFFIX): New macro.
	(cplus_suffix): New static variable.
	(is_abspath): New static function.
	(in_system_include_dir): Handle DOS style pathnames.
	(file_could_be_converted): Likewise.
	(file_normally_convertible): Likewise.
	(directory_specified_p): Likewise.
	(file_excluded_p): Likewise.
	(abspath): Likewise.
	(shortpath): Likewise.
	(referenced_file_is_newer): Likewise.
	(save_def_or_dec): Likewise.
	(do_processing): Likewise.
	(main): Likewise.
	(edit_file): Likewise. Use rename instead of link.
	(rename_c_file): Likewise. Don't rename syscalls file.
	(munge_compile_params): Define null device for DOS based systems.
	(process_aux_info_file): Use binary mode if appliable.
	(edit_file): Likewise.

	* invoke.texi (Running Protoize): Document C++ suffixes used. 

	* ginclude/stdarg.h: Use RC_INVOKED guard needed for windows32 
	resource compilation.
	(__gnuc_va_list): Define for Mingw.
	* ginclude/stddef.h: Use RC_INVOKED guard needed for windows32 
	resource compilation.

	* i386/cygwin.h (STARTFILE_SPEC): Support -shared option, and
	add correct entry point for DLLs.
	(LINK_SPEC): Likewise.
	* i386/mingw32.h (STARTFILE_SPEC): Likewise.
	(LINK_SPEC): Likewise.
	* i386/crtdll.h (STARTFILE_SPEC): Likewise.

Sun Dec 12 20:35:14 1999  Mumit Khan  <khan@xraylith.wisc.edu>

	* i386/config/winnt.c (i386_pe_dllimport_p): Don't import inline
	functions, and C++ methods and vtables.
	(i386_pe_mark_dllimport): Handle illegal dllimports.

	* gcc.c (load_specs): New static function.
	(read_specs): Use.
	(lookup_compiler): Handle it better.

Fri Nov  5 03:52:57 1999  Mumit Khan  <khan@xraylith.wisc.edu>

	* gcc.c (lookup_compiler): Handle case-insensitive filename
	extensions for DOS-based systems.
	(HAVE_DOS_BASED_FILE_SYSTEM): Fix typo.
	* i386/xm-djgpp.h: Likewise.

Fri Nov  5 02:32:32 1999  Mumit Khan  <khan@xraylith.wisc.edu>

	* gthr-win32.h (__gthread_active_p): Support Mingw MT runtime.
	(__gthread_key_create): Likewise. 
 	(__gthread_key_dtor):  Likewise.
	(__gthread_once): Fix logic.
	(__gthread_key_delete): Cast away constness.

	* i386/cygwin.h (SUBTARGET_SWITCHES): Add -mthreads option.
	* invoke.texi: Document.
	* i386/mingw32.h (CPP_SPEC): Use.
	(LIBGCC_SPEC): Likewise.
	* i386/crtdll.h (LIBGCC_SPEC): Likewise.

Tue Aug 17 21:36:08 1999  Mumit Khan  <khan@xraylith.wisc.edu>

	* gthr-win32.h: New file.

Sat Aug 28 17:16:08 1999  Mumit Khan  <khan@xraylith.wisc.edu>

	* i386/winnt.c (export_list): New type.
	(exports_head): Rename to
	(export_head):  this.
	(i386_pe_record_exported_symbol): Add is_data flag.
	(i386_pe_asm_file_end): Emit directive for exported variables.
	* i386/cygwin.h (i386_pe_record_exported_symbol): Update
	prototype.
	* i386/cygwin.h (ASM_OUTPUT_COMMON): Specify symbol type.
	(ASM_DECLARE_OBJECT_NAME): Likewise.
	(ASM_DECLARE_FUNCTION_NAME): Likewise.
	* i386/uwin.h (ASM_DECLARE_FUNCTION_NAME): Likewise.

Wed Aug 18 18:56:23 CDT 1999  Mumit Khan  <khan@xraylith.wisc.edu>

	* i386/crtdll.h (STARTFILE_SPEC): Add -pg profiling support.
	* i386/mingw32.h (LIB_SPEC): Likewise.
	(STARTFILE_SPEC): Likewise.
	* i386/uwin.h (LIB_SPEC): Likewise.
	(STARTFILE_SPEC): Likewise.

	* i386/mingw32.h (SUBTARGET_PROLOGUE): Override Cygwin definition.
	* i386/uwin.h (SUBTARGET_PROLOGUE): Likewise.

Fri Aug 13 11:18:44 1999  Mumit Khan  <khan@xraylith.wisc.edu>

	* configure.in: Handle --disable/enable-win32-registry.
	* install.texi: Document --disable/enable-win32-registry.
	* acconfig.h (ENABLE_WIN32_REGISTRY): New macro.
	(WIN32_REGISTRY_KEY): New macro.
	* prefix.c: Use to enable/disable win32-specific code.
	(lookup_key): Use versioned key.
	* configure: Regenerate.
	* config.in: Likewise.

Sat Aug  7 00:38:21 1999  Mumit Khan  <khan@xraylith.wisc.edu>
	
	* i386/winnt.c (i386_pe_valid_decl_attribute_p): Recognize
	shared as a valid attribute.
	* i386/cygwin.h (ASM_OUTPUT_SECTION): Handle shared attribute.
	* extend.texi: Document `shared' variable attribute.

Wed Aug  4 22:25:17 1999  Mumit Khan  <khan@xraylith.wisc.edu>

	* i386/cygwin.h (ASM_OUTPUT_ALIGNED_BSS): Define.

Thu Jul 15 20:27:06 1999  Mumit Khan  <khan@xraylith.wisc.edu>

	* cccp.c (INO_T_EQ): Disable inode-based optimization for Cygwin.
	* cppfiles.c (INO_T_EQ): Likewise.

Tue Jul 20 22:56:35 1999  Mumit Khan  <khan@xraylith.wisc.edu>

	* i386/uwin.h (LINK_SPEC): Add -u _main when building executables.
	* i386/xm-uwin.h (HAVE_BCOPY): Undefine.

Sat Jul 10 12:07:51 1999  Mumit Khan  <khan@xraylith.wisc.edu>

	* i386/uwin.h (ASM_DECLARE_FUNCTION): Update from Cygwin.
	(ASM_FILE_END): Use the default for ix86-pe.
	* fixinc/mkfixinc.sh: Don't fix uwin headers.

Tue Jul  6 20:36:41 1999  Mumit Khan  <khan@xraylith.wisc.edu>

	* i386/uwin.h (MD_STARTFILE_PREFIX): Define.

Fri Jul  2 22:13:14 1999  Mumit Khan  <khan@xraylith.wisc.edu>

	* c-pragma.h (PRAGMA_INSERT_ATTRIBUTES): Delete macro.
	(insert_pack_attributes): Delete prototype.
	(enum pragma_state): Simplify.

	* c-pragma.c (struct align_stack): Lose num_pushes field.
	(push_alignment): Remove redundant check for valid alignment;
	always push on stack.
	(pop_alignment): Update prototype. Implement combination rule.
	(insert_pack_attributes): Lose.
	(handle_pragma_token): Document syntax. Simplify pack(push/pop)
	attributes and implement documented syntax.

Sun Jul  4 13:18:23 1999  Mumit Khan  <khan@xraylith.wisc.edu>

	* i386/cygwin.h (PCC_BITFIELD_TYPE_MATTERS): Fix typo and 
	define to be 1.
	(GROUP_BITFIELDS_BY_ALIGN): Define.

Mon Apr 26 12:25:41 1999 Donn Terry (donn@interix.com)

	* flags.h (flag_native_struct): New boolean.
	* tree.h (TYPE_NATIVE): New macro.
	(tree_type): Add native_flag.
	* c-common.c (attrs): Add A_NATIVE, A_GCC_PACK to enum.
	(init_attributes): Set them up.
	(decl_attributes): Parse them, setting flag_native_struct.
	* c-decl.c (start_struct): Propigate TYPE_NATIVE.
	* stor-layout.c (layout_record): Honor GROUP_BITFIELDS_BY_ALIGN.
	(layout_union): Likewise.
	* toplev.c (lang_independent_options): Add native-struct and
	gcc-struct flags.
	(flag_native_struct): Initialize.
	* config/i386/i386-interix.h (PCC_BITFIELD_TYPE_TEST): remove.
	* config/alpha/alpha-interix.h (PCC_BITFIELD_TYPE_TEST): remove.

Sat Jun 12 15:56:40 1999  Alastair J. Houghton <ajh8@doc.ic.ac.uk>
			  Mumit Khan  <khan@xraylith.wisc.edu>

	* c-parse.in (component_decl): Support anonymous struct/union.
	(%expect): Update.
	* c-parse.y: Regenerate.
	* c-parse.c: Likewise.
	* objc/objc-parse.y: Likewise.
	* objc/objc-parse.c: Likewise.
	* c-decl.c (finish_struct): Don't sort the fields.

Tue Sep  1 14:22:53 1998  Mumit Khan  <khan@xraylith.wisc.edu>

	* libgcc2.c (inhibit_libc): Do not define when cross-compiling for
	Cygwin or Mingw or UWIN targets.

Wed Aug 12 18:18:16 1998  Mumit Khan  <khan@xraylith.wisc.edu>

	* i386/winnt.c (i386_pe_dllexport_p): Check TREE_TYPE for
	attributes as well for C++ class members.
	(i386_pe_dllimport_p): Likewise.

Wed Jun  9 16:57:11 1999  Mumit Khan  <khan@xraylith.wisc.edu>

	* gcc.c (STANDARD_BINDIR_PREFIX): Provide default.

Fri Feb  5 14:22:01 1999  Mumit Khan  <khan@xraylith.wisc.edu>
        
	* gcc.c (make_relative_prefix): Handle the HAVE_EXECUTABLE_SUFFIX
	case.

Fri Mar 13 17:54:04 1998  Michael Meissner  <meissner@cygnus.com>

        * gcc.c (DIR_UP): If not defined, define as "..".
        (standard_bindir_prefix): New static, holds target location to
        install binaries.
        (split_directories): New function to split a filename into
        component directories.
        (free_split_directories): New function, release memory allocated
        by split_directories.
        (make_relative_prefix): New function, make a relative pathname if
        the compiler is not in the expected location.
        (process_command): Use GET_ENVIRONMENT to read GCC_EXEC_PREFIX.
        If GCC_EXEC_PREFIX was not specified, see if we can figure out an
        appropriate prefix from argv[0].

        * Makefile.in (gcc.o): Define STANDARD_BINDIR_PREFIX.

Mon May 10 09:11:23 1993  Ian Lance Taylor  (ian@cygnus.com)

	* Makefile.in (cccp.o): Use $(libsubdir)/$(unlibsubdir) for
	LOCAL_INCLUDE_DIR, so that a native compiler can find assert.h via
	GCC_EXEC_PREFIX.

Fri May  7 09:16:10 1993  Ian Lance Taylor  (ian@cygnus.com)

	* Makefile.in (gcc.o): Pass STANDARD_STARTFILE_PREFIX as
	$(unlibsubdir) rather than $(libdir) so that native compilations can
	find $(libdir).


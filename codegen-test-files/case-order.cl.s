# start of generated code

# coding global data 
	.data
	.align	2
	.globl	class_nameTab
	.globl	Main_protObj
	.globl	Int_protObj
	.globl	String_protObj
	.globl	bool_const0
	.globl	bool_const1
	.globl	_int_tag
	.globl	_bool_tag
	.globl	_string_tag
_int_tag:
	.word	3
_bool_tag:
	.word	4
_string_tag:
	.word	5

# choosing gc
	.globl	_MemMgr_INITIALIZER
_MemMgr_INITIALIZER:
	.word	_NoGC_Init
	.globl	_MemMgr_COLLECTOR
_MemMgr_COLLECTOR:
	.word	_NoGC_Collect
	.globl	_MemMgr_TEST
_MemMgr_TEST:
	.word	0

# coding constants
	.word	-1
str_const13:
	.word	5
	.word	5
	.word	String_dispatch_tab
	.word	int_const0
	.byte	0	
	.align	2
	.word	-1
str_const12:
	.word	5
	.word	6
	.word	String_dispatch_tab
	.word	int_const1
	.ascii	"Main"
	.byte	0	
	.align	2
	.word	-1
str_const11:
	.word	5
	.word	6
	.word	String_dispatch_tab
	.word	int_const2
	.ascii	"String"
	.byte	0	
	.align	2
	.word	-1
str_const10:
	.word	5
	.word	6
	.word	String_dispatch_tab
	.word	int_const1
	.ascii	"Bool"
	.byte	0	
	.align	2
	.word	-1
str_const9:
	.word	5
	.word	5
	.word	String_dispatch_tab
	.word	int_const3
	.ascii	"Int"
	.byte	0	
	.align	2
	.word	-1
str_const8:
	.word	5
	.word	5
	.word	String_dispatch_tab
	.word	int_const4
	.ascii	"IO"
	.byte	0	
	.align	2
	.word	-1
str_const7:
	.word	5
	.word	6
	.word	String_dispatch_tab
	.word	int_const2
	.ascii	"Object"
	.byte	0	
	.align	2
	.word	-1
str_const6:
	.word	5
	.word	7
	.word	String_dispatch_tab
	.word	int_const5
	.ascii	"_prim_slot"
	.byte	0	
	.align	2
	.word	-1
str_const5:
	.word	5
	.word	7
	.word	String_dispatch_tab
	.word	int_const6
	.ascii	"SELF_TYPE"
	.byte	0	
	.align	2
	.word	-1
str_const4:
	.word	5
	.word	7
	.word	String_dispatch_tab
	.word	int_const6
	.ascii	"_no_class"
	.byte	0	
	.align	2
	.word	-1
str_const3:
	.word	5
	.word	8
	.word	String_dispatch_tab
	.word	int_const7
	.ascii	"<basic class>"
	.byte	0	
	.align	2
	.word	-1
str_const2:
	.word	5
	.word	6
	.word	String_dispatch_tab
	.word	int_const8
	.ascii	"main\n"
	.byte	0	
	.align	2
	.word	-1
str_const1:
	.word	5
	.word	6
	.word	String_dispatch_tab
	.word	int_const9
	.ascii	"object\n"
	.byte	0	
	.align	2
	.word	-1
str_const0:
	.word	5
	.word	8
	.word	String_dispatch_tab
	.word	int_const10
	.ascii	"./case-order.cl"
	.byte	0	
	.align	2
	.word	-1
int_const10:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	15
	.word	-1
int_const9:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	7
	.word	-1
int_const8:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	5
	.word	-1
int_const7:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	13
	.word	-1
int_const6:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	9
	.word	-1
int_const5:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	10
	.word	-1
int_const4:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	2
	.word	-1
int_const3:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	3
	.word	-1
int_const2:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	6
	.word	-1
int_const1:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	4
	.word	-1
int_const0:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	0
	.word	-1
bool_const0:
	.word	4
	.word	4
	.word	Bool_dispatch_tab
	.word	0
	.word	-1
bool_const1:
	.word	4
	.word	4
	.word	Bool_dispatch_tab
	.word	1

# Declare Class Tag
	.globl	_IO_tag
	.globl	_Main_tag
	.globl	_Object_tag

# Class Tag Definition
_IO_tag:
	.word	1
_Main_tag:
	.word	2
_Object_tag:
	.word	0

# Class Name String Table
class_nameTab:
	.word	str_const7
	.word	str_const8
	.word	str_const12
	.word	str_const9
	.word	str_const10
	.word	str_const11

# Class Dispatch Table
Bool_dispatch_tab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy

IO_dispatch_tab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int

Int_dispatch_tab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy

Main_dispatch_tab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Main.main

Object_dispatch_tab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy

String_dispatch_tab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	String.length
	.word	String.concat
	.word	String.substr


# Class Prototype
	.word	-1
Bool_protObj:
	.word	4
	.word	4
	.word	Bool_dispatch_tab
	.word	0
	.word	-1
IO_protObj:
	.word	1
	.word	3
	.word	IO_dispatch_tab
	.word	-1
Int_protObj:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	0
	.word	-1
Main_protObj:
	.word	2
	.word	3
	.word	Main_dispatch_tab
	.word	-1
Object_protObj:
	.word	0
	.word	3
	.word	Object_dispatch_tab
	.word	-1
String_protObj:
	.word	5
	.word	5
	.word	String_dispatch_tab
	.word	int_const0
	.word	0

class_direct_parent_tab:
	.word	-1 #Object, tag_no:0, , tag_no:-1
	.word	0 #IO, tag_no:1, Object, tag_no:0
	.word	1 #Main, tag_no:2, IO, tag_no:1
	.word	0 #Int, tag_no:3, Object, tag_no:0
	.word	0 #Bool, tag_no:4, Object, tag_no:0
	.word	0 #String, tag_no:5, Object, tag_no:0

class_prot_obj_tab:
	.word	Object_protObj
	.word	IO_protObj
	.word	Main_protObj
	.word	Int_protObj
	.word	Bool_protObj
	.word	String_protObj

class_init_tab:
	.word	Object_init
	.word	IO_init
	.word	Main_init
	.word	Int_init
	.word	Bool_init
	.word	String_init

	.globl	heap_start
heap_start:
	.word	0

	.text
	.globl	Main_init
	.globl	Int_init
	.globl	String_init
	.globl	Bool_init
	.globl	Main.main

# Class Init Method
Bool_init:
	addiu	$sp	$sp	-12
	sw	$fp	12($sp)
	sw	$s0	8($sp)
	sw	$ra	4($sp)
	addiu	$fp	$sp	4
	move	$s0	$a0
	jal	Object_init
	move	$a0	$s0
	lw	$fp	12($sp)
	lw	$s0	8($sp)
	lw	$ra	4($sp)
	addiu	$sp	$sp	12
	jr	$ra
IO_init:
	addiu	$sp	$sp	-12
	sw	$fp	12($sp)
	sw	$s0	8($sp)
	sw	$ra	4($sp)
	addiu	$fp	$sp	4
	move	$s0	$a0
	jal	Object_init
	move	$a0	$s0
	lw	$fp	12($sp)
	lw	$s0	8($sp)
	lw	$ra	4($sp)
	addiu	$sp	$sp	12
	jr	$ra
Int_init:
	addiu	$sp	$sp	-12
	sw	$fp	12($sp)
	sw	$s0	8($sp)
	sw	$ra	4($sp)
	addiu	$fp	$sp	4
	move	$s0	$a0
	jal	Object_init
	move	$a0	$s0
	lw	$fp	12($sp)
	lw	$s0	8($sp)
	lw	$ra	4($sp)
	addiu	$sp	$sp	12
	jr	$ra
Main_init:
	addiu	$sp	$sp	-12
	sw	$fp	12($sp)
	sw	$s0	8($sp)
	sw	$ra	4($sp)
	addiu	$fp	$sp	4
	move	$s0	$a0
	jal	IO_init
	move	$a0	$s0
	lw	$fp	12($sp)
	lw	$s0	8($sp)
	lw	$ra	4($sp)
	addiu	$sp	$sp	12
	jr	$ra
Object_init:
	addiu	$sp	$sp	-12
	sw	$fp	12($sp)
	sw	$s0	8($sp)
	sw	$ra	4($sp)
	addiu	$fp	$sp	4
	move	$s0	$a0
	move	$a0	$s0
	lw	$fp	12($sp)
	lw	$s0	8($sp)
	lw	$ra	4($sp)
	addiu	$sp	$sp	12
	jr	$ra
String_init:
	addiu	$sp	$sp	-12
	sw	$fp	12($sp)
	sw	$s0	8($sp)
	sw	$ra	4($sp)
	addiu	$fp	$sp	4
	move	$s0	$a0
	jal	Object_init
	move	$a0	$s0
	lw	$fp	12($sp)
	lw	$s0	8($sp)
	lw	$ra	4($sp)
	addiu	$sp	$sp	12
	jr	$ra

# Class Methods 

Main.main:
	addiu	$sp	$sp	-20
	sw	$fp	20($sp)
	sw	$s0	16($sp)
	sw	$ra	12($sp)
	addiu	$fp	$sp	12
	move	$s0	$a0
	move	$a0	$s0
	sw	$a0	-4($fp)
	lw	$a0	-4($fp)
	bne	$a0 $zero label0
	la	$a0 str_const0
	li	$t1 1
	jal	_case_abort2
label0:
	lw	$t1	0($a0)
# find ancestor
label3:
	li	$t2 0
	beq	$t1 $t2 label1
	li	$t2 2
	beq	$t1 $t2 label2
	li	$t2 0
	beq	$t1 $t2 label4
	la	$t2 class_direct_parent_tab
	li	$t3 4
	mul	$t1	$t1	$t3
	add	$t1	$t1	$t2
	lw	$t1	0($t1)
	b	label3
label4:
	jal	_case_abort
label1:
	sw	$a0	-8($fp)
# dispatch:out_string
# push arg :0
	la	$a0 str_const1
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label6
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label6:
	lw	$t1	8($a0)
	lw	$t1	12($t1)
	jalr	$t1
# dispatch:out_string end
	b	label5
label2:
	sw	$a0	-8($fp)
# dispatch:out_string
# push arg :0
	la	$a0 str_const2
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label7
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label7:
	lw	$t1	8($a0)
	lw	$t1	12($t1)
	jalr	$t1
# dispatch:out_string end
	b	label5
label5:
	lw	$fp	20($sp)
	lw	$s0	16($sp)
	lw	$ra	12($sp)
	addiu	$sp	$sp	20
	addiu	$sp	$sp	0
	jr	$ra


# end of generated code

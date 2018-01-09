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
	.word	2
_bool_tag:
	.word	3
_string_tag:
	.word	4

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
	.word	4
	.word	5
	.word	String_dispatch_tab
	.word	int_const1
	.byte	0	
	.align	2
	.word	-1
str_const12:
	.word	4
	.word	6
	.word	String_dispatch_tab
	.word	int_const3
	.ascii	"Main"
	.byte	0	
	.align	2
	.word	-1
str_const11:
	.word	4
	.word	5
	.word	String_dispatch_tab
	.word	int_const4
	.ascii	"B"
	.byte	0	
	.align	2
	.word	-1
str_const10:
	.word	4
	.word	5
	.word	String_dispatch_tab
	.word	int_const4
	.ascii	"A"
	.byte	0	
	.align	2
	.word	-1
str_const9:
	.word	4
	.word	6
	.word	String_dispatch_tab
	.word	int_const5
	.ascii	"String"
	.byte	0	
	.align	2
	.word	-1
str_const8:
	.word	4
	.word	6
	.word	String_dispatch_tab
	.word	int_const3
	.ascii	"Bool"
	.byte	0	
	.align	2
	.word	-1
str_const7:
	.word	4
	.word	5
	.word	String_dispatch_tab
	.word	int_const2
	.ascii	"Int"
	.byte	0	
	.align	2
	.word	-1
str_const6:
	.word	4
	.word	5
	.word	String_dispatch_tab
	.word	int_const6
	.ascii	"IO"
	.byte	0	
	.align	2
	.word	-1
str_const5:
	.word	4
	.word	6
	.word	String_dispatch_tab
	.word	int_const5
	.ascii	"Object"
	.byte	0	
	.align	2
	.word	-1
str_const4:
	.word	4
	.word	7
	.word	String_dispatch_tab
	.word	int_const7
	.ascii	"_prim_slot"
	.byte	0	
	.align	2
	.word	-1
str_const3:
	.word	4
	.word	7
	.word	String_dispatch_tab
	.word	int_const8
	.ascii	"SELF_TYPE"
	.byte	0	
	.align	2
	.word	-1
str_const2:
	.word	4
	.word	7
	.word	String_dispatch_tab
	.word	int_const8
	.ascii	"_no_class"
	.byte	0	
	.align	2
	.word	-1
str_const1:
	.word	4
	.word	8
	.word	String_dispatch_tab
	.word	int_const9
	.ascii	"<basic class>"
	.byte	0	
	.align	2
	.word	-1
str_const0:
	.word	4
	.word	9
	.word	String_dispatch_tab
	.word	int_const10
	.ascii	"./objectequality.cl"
	.byte	0	
	.align	2
	.word	-1
int_const10:
	.word	2
	.word	4
	.word	Int_dispatch_tab
	.word	19
	.word	-1
int_const9:
	.word	2
	.word	4
	.word	Int_dispatch_tab
	.word	13
	.word	-1
int_const8:
	.word	2
	.word	4
	.word	Int_dispatch_tab
	.word	9
	.word	-1
int_const7:
	.word	2
	.word	4
	.word	Int_dispatch_tab
	.word	10
	.word	-1
int_const6:
	.word	2
	.word	4
	.word	Int_dispatch_tab
	.word	2
	.word	-1
int_const5:
	.word	2
	.word	4
	.word	Int_dispatch_tab
	.word	6
	.word	-1
int_const4:
	.word	2
	.word	4
	.word	Int_dispatch_tab
	.word	1
	.word	-1
int_const3:
	.word	2
	.word	4
	.word	Int_dispatch_tab
	.word	4
	.word	-1
int_const2:
	.word	2
	.word	4
	.word	Int_dispatch_tab
	.word	3
	.word	-1
int_const1:
	.word	2
	.word	4
	.word	Int_dispatch_tab
	.word	0
	.word	-1
int_const0:
	.word	2
	.word	4
	.word	Int_dispatch_tab
	.word	5
	.word	-1
bool_const0:
	.word	3
	.word	4
	.word	Bool_dispatch_tab
	.word	0
	.word	-1
bool_const1:
	.word	3
	.word	4
	.word	Bool_dispatch_tab
	.word	1

# Declare Class Tag
	.globl	_A_tag
	.globl	_B_tag
	.globl	_IO_tag
	.globl	_Main_tag
	.globl	_Object_tag

# Class Tag Definition
_A_tag:
	.word	5
_B_tag:
	.word	6
_IO_tag:
	.word	1
_Main_tag:
	.word	7
_Object_tag:
	.word	0

# Class Name String Table
class_nameTab:
	.word	str_const5
	.word	str_const6
	.word	str_const7
	.word	str_const8
	.word	str_const9
	.word	str_const10
	.word	str_const11
	.word	str_const12

# Class Dispatch Table
A_dispatch_tab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	A.foo

B_dispatch_tab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	A.foo

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
A_protObj:
	.word	5
	.word	4
	.word	A_dispatch_tab
	.word	int_const1
	.word	-1
B_protObj:
	.word	6
	.word	4
	.word	B_dispatch_tab
	.word	int_const1
	.word	-1
Bool_protObj:
	.word	3
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
	.word	2
	.word	4
	.word	Int_dispatch_tab
	.word	0
	.word	-1
Main_protObj:
	.word	7
	.word	3
	.word	Main_dispatch_tab
	.word	-1
Object_protObj:
	.word	0
	.word	3
	.word	Object_dispatch_tab
	.word	-1
String_protObj:
	.word	4
	.word	5
	.word	String_dispatch_tab
	.word	int_const1
	.word	0

class_direct_parent_tab:
	.word	-1 #Object, tag_no:0, , tag_no:-1
	.word	0 #IO, tag_no:1, Object, tag_no:0
	.word	0 #Int, tag_no:2, Object, tag_no:0
	.word	0 #Bool, tag_no:3, Object, tag_no:0
	.word	0 #String, tag_no:4, Object, tag_no:0
	.word	0 #A, tag_no:5, Object, tag_no:0
	.word	5 #B, tag_no:6, A, tag_no:5
	.word	0 #Main, tag_no:7, Object, tag_no:0

class_prot_obj_tab:
	.word	Object_protObj
	.word	IO_protObj
	.word	Int_protObj
	.word	Bool_protObj
	.word	String_protObj
	.word	A_protObj
	.word	B_protObj
	.word	Main_protObj

class_init_tab:
	.word	Object_init
	.word	IO_init
	.word	Int_init
	.word	Bool_init
	.word	String_init
	.word	A_init
	.word	B_init
	.word	Main_init

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
A_init:
	addiu	$sp	$sp	-12
	sw	$fp	12($sp)
	sw	$s0	8($sp)
	sw	$ra	4($sp)
	addiu	$fp	$sp	4
	move	$s0	$a0
	jal	Object_init
	la	$a0 int_const0
	sw	$a0	12($s0)
	move	$a0	$s0
	lw	$fp	12($sp)
	lw	$s0	8($sp)
	lw	$ra	4($sp)
	addiu	$sp	$sp	12
	jr	$ra
B_init:
	addiu	$sp	$sp	-12
	sw	$fp	12($sp)
	sw	$s0	8($sp)
	sw	$ra	4($sp)
	addiu	$fp	$sp	4
	move	$s0	$a0
	jal	A_init
	move	$a0	$s0
	lw	$fp	12($sp)
	lw	$s0	8($sp)
	lw	$ra	4($sp)
	addiu	$sp	$sp	12
	jr	$ra
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
	jal	Object_init
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

A.foo:
	addiu	$sp	$sp	-12
	sw	$fp	12($sp)
	sw	$s0	8($sp)
	sw	$ra	4($sp)
	addiu	$fp	$sp	4
	move	$s0	$a0
	lw	$a0	12($fp)
	sw	$a0	12($s0)
	move	$a0	$s0
	lw	$fp	12($sp)
	lw	$s0	8($sp)
	lw	$ra	4($sp)
	addiu	$sp	$sp	12
	addiu	$sp	$sp	4
	jr	$ra

Main.main:
	addiu	$sp	$sp	-28
	sw	$fp	28($sp)
	sw	$s0	24($sp)
	sw	$ra	20($sp)
	addiu	$fp	$sp	20
	move	$s0	$a0
	la	$a0 B_protObj
	jal	Object.copy
	jal	B_init
	sw	$a0	-4($fp)
	lw	$a0	-4($fp)
	sw	$a0	-8($fp)
	lw	$a0	-4($fp)
	sw	$a0	-12($fp)
	la	$a0	bool_const1
	lw	$t1	-8($fp)
	lw	$t2	-12($fp)
	beq	$t1 $t2 label0
	la	$a1	bool_const0
	jal	equality_test
label0:
	lw	$t1	12($a0)
	beqz	$t1 label1
	la	$a0 int_const1
	b	label2
label1:
# dispatch:abort
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label3
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label3:
	lw	$t1	8($a0)
	lw	$t1	0($t1)
	jalr	$t1
# dispatch:abort end
label2:
	lw	$a0	-4($fp)
	sw	$a0	-8($fp)
	la	$a0 B_protObj
	jal	Object.copy
	jal	B_init
	sw	$a0	-12($fp)
	la	$a0	bool_const1
	lw	$t1	-8($fp)
	lw	$t2	-12($fp)
	beq	$t1 $t2 label4
	la	$a1	bool_const0
	jal	equality_test
label4:
	lw	$t1	12($a0)
	beqz	$t1 label5
# dispatch:abort
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label7
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label7:
	lw	$t1	8($a0)
	lw	$t1	0($t1)
	jalr	$t1
# dispatch:abort end
	b	label6
label5:
	la	$a0 int_const1
label6:
	la	$a0 A_protObj
	jal	Object.copy
	jal	A_init
	sw	$a0	-8($fp)
	la	$a0 A_protObj
	jal	Object.copy
	jal	A_init
	sw	$a0	-12($fp)
	la	$a0	bool_const1
	lw	$t1	-8($fp)
	lw	$t2	-12($fp)
	beq	$t1 $t2 label8
	la	$a1	bool_const0
	jal	equality_test
label8:
	lw	$t1	12($a0)
	beqz	$t1 label9
# dispatch:abort
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label11
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label11:
	lw	$t1	8($a0)
	lw	$t1	0($t1)
	jalr	$t1
# dispatch:abort end
	b	label10
label9:
	la	$a0 int_const1
label10:
	lw	$a0	-4($fp)
	sw	$a0	-8($fp)
	lw	$a0	-8($fp)
	sw	$a0	-12($fp)
	lw	$a0	-4($fp)
	sw	$a0	-16($fp)
	la	$a0	bool_const1
	lw	$t1	-12($fp)
	lw	$t2	-16($fp)
	beq	$t1 $t2 label12
	la	$a1	bool_const0
	jal	equality_test
label12:
	lw	$t1	12($a0)
	beqz	$t1 label13
	la	$a0 int_const1
	b	label14
label13:
# dispatch:abort
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label15
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label15:
	lw	$t1	8($a0)
	lw	$t1	0($t1)
	jalr	$t1
# dispatch:abort end
label14:
# dispatch:foo
# push arg :0
	la	$a0 int_const2
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# evaluate dispatch expr
	lw	$a0	-8($fp)
	bne	$a0 $zero label16
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label16:
	lw	$t1	8($a0)
	lw	$t1	12($t1)
	jalr	$t1
# dispatch:foo end
	sw	$a0	-12($fp)
	lw	$a0	-4($fp)
	sw	$a0	-16($fp)
	la	$a0	bool_const1
	lw	$t1	-12($fp)
	lw	$t2	-16($fp)
	beq	$t1 $t2 label17
	la	$a1	bool_const0
	jal	equality_test
label17:
	lw	$t1	12($a0)
	beqz	$t1 label18
	la	$a0 int_const1
	b	label19
label18:
# dispatch:abort
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label20
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label20:
	lw	$t1	8($a0)
	lw	$t1	0($t1)
	jalr	$t1
# dispatch:abort end
label19:
	li	$a0	0
	sw	$a0	-4($fp)
	li	$a0	0
	sw	$a0	-8($fp)
	lw	$a0	-4($fp)
	sw	$a0	-12($fp)
	lw	$a0	-8($fp)
	sw	$a0	-16($fp)
	la	$a0	bool_const1
	lw	$t1	-12($fp)
	lw	$t2	-16($fp)
	beq	$t1 $t2 label21
	la	$a1	bool_const0
	jal	equality_test
label21:
	lw	$t1	12($a0)
	beqz	$t1 label22
	la	$a0 int_const1
	b	label23
label22:
# dispatch:abort
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label24
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label24:
	lw	$t1	8($a0)
	lw	$t1	0($t1)
	jalr	$t1
# dispatch:abort end
label23:
	lw	$fp	28($sp)
	lw	$s0	24($sp)
	lw	$ra	20($sp)
	addiu	$sp	$sp	28
	addiu	$sp	$sp	0
	jr	$ra


# end of generated code

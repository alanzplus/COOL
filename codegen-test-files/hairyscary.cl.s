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
	.word	6
_bool_tag:
	.word	7
_string_tag:
	.word	8

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
str_const16:
	.word	8
	.word	5
	.word	String_dispatch_tab
	.word	int_const2
	.byte	0	
	.align	2
	.word	-1
str_const15:
	.word	8
	.word	6
	.word	String_dispatch_tab
	.word	int_const3
	.ascii	"Main"
	.byte	0	
	.align	2
	.word	-1
str_const14:
	.word	8
	.word	6
	.word	String_dispatch_tab
	.word	int_const3
	.ascii	"Bazz"
	.byte	0	
	.align	2
	.word	-1
str_const13:
	.word	8
	.word	6
	.word	String_dispatch_tab
	.word	int_const3
	.ascii	"Razz"
	.byte	0	
	.align	2
	.word	-1
str_const12:
	.word	8
	.word	5
	.word	String_dispatch_tab
	.word	int_const4
	.ascii	"Bar"
	.byte	0	
	.align	2
	.word	-1
str_const11:
	.word	8
	.word	5
	.word	String_dispatch_tab
	.word	int_const4
	.ascii	"Foo"
	.byte	0	
	.align	2
	.word	-1
str_const10:
	.word	8
	.word	6
	.word	String_dispatch_tab
	.word	int_const5
	.ascii	"String"
	.byte	0	
	.align	2
	.word	-1
str_const9:
	.word	8
	.word	6
	.word	String_dispatch_tab
	.word	int_const3
	.ascii	"Bool"
	.byte	0	
	.align	2
	.word	-1
str_const8:
	.word	8
	.word	5
	.word	String_dispatch_tab
	.word	int_const4
	.ascii	"Int"
	.byte	0	
	.align	2
	.word	-1
str_const7:
	.word	8
	.word	5
	.word	String_dispatch_tab
	.word	int_const0
	.ascii	"IO"
	.byte	0	
	.align	2
	.word	-1
str_const6:
	.word	8
	.word	6
	.word	String_dispatch_tab
	.word	int_const5
	.ascii	"Object"
	.byte	0	
	.align	2
	.word	-1
str_const5:
	.word	8
	.word	7
	.word	String_dispatch_tab
	.word	int_const6
	.ascii	"_prim_slot"
	.byte	0	
	.align	2
	.word	-1
str_const4:
	.word	8
	.word	7
	.word	String_dispatch_tab
	.word	int_const7
	.ascii	"SELF_TYPE"
	.byte	0	
	.align	2
	.word	-1
str_const3:
	.word	8
	.word	7
	.word	String_dispatch_tab
	.word	int_const7
	.ascii	"_no_class"
	.byte	0	
	.align	2
	.word	-1
str_const2:
	.word	8
	.word	8
	.word	String_dispatch_tab
	.word	int_const8
	.ascii	"<basic class>"
	.byte	0	
	.align	2
	.word	-1
str_const1:
	.word	8
	.word	7
	.word	String_dispatch_tab
	.word	int_const6
	.ascii	"do nothing"
	.byte	0	
	.align	2
	.word	-1
str_const0:
	.word	8
	.word	8
	.word	String_dispatch_tab
	.word	int_const9
	.ascii	"./hairyscary.cl"
	.byte	0	
	.align	2
	.word	-1
int_const9:
	.word	6
	.word	4
	.word	Int_dispatch_tab
	.word	15
	.word	-1
int_const8:
	.word	6
	.word	4
	.word	Int_dispatch_tab
	.word	13
	.word	-1
int_const7:
	.word	6
	.word	4
	.word	Int_dispatch_tab
	.word	9
	.word	-1
int_const6:
	.word	6
	.word	4
	.word	Int_dispatch_tab
	.word	10
	.word	-1
int_const5:
	.word	6
	.word	4
	.word	Int_dispatch_tab
	.word	6
	.word	-1
int_const4:
	.word	6
	.word	4
	.word	Int_dispatch_tab
	.word	3
	.word	-1
int_const3:
	.word	6
	.word	4
	.word	Int_dispatch_tab
	.word	4
	.word	-1
int_const2:
	.word	6
	.word	4
	.word	Int_dispatch_tab
	.word	0
	.word	-1
int_const1:
	.word	6
	.word	4
	.word	Int_dispatch_tab
	.word	1
	.word	-1
int_const0:
	.word	6
	.word	4
	.word	Int_dispatch_tab
	.word	2
	.word	-1
bool_const0:
	.word	7
	.word	4
	.word	Bool_dispatch_tab
	.word	0
	.word	-1
bool_const1:
	.word	7
	.word	4
	.word	Bool_dispatch_tab
	.word	1

# Declare Class Tag
	.globl	_Bar_tag
	.globl	_Bazz_tag
	.globl	_Foo_tag
	.globl	_IO_tag
	.globl	_Main_tag
	.globl	_Object_tag
	.globl	_Razz_tag

# Class Tag Definition
_Bar_tag:
	.word	5
_Bazz_tag:
	.word	2
_Foo_tag:
	.word	3
_IO_tag:
	.word	1
_Main_tag:
	.word	9
_Object_tag:
	.word	0
_Razz_tag:
	.word	4

# Class Name String Table
class_nameTab:
	.word	str_const6
	.word	str_const7
	.word	str_const14
	.word	str_const11
	.word	str_const13
	.word	str_const12
	.word	str_const8
	.word	str_const9
	.word	str_const10
	.word	str_const15

# Class Dispatch Table
Bar_dispatch_tab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Bazz.printh
	.word	Foo.doh

Bazz_dispatch_tab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Bazz.printh
	.word	Bazz.doh

Bool_dispatch_tab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy

Foo_dispatch_tab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Bazz.printh
	.word	Foo.doh

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

Razz_dispatch_tab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Bazz.printh
	.word	Foo.doh

String_dispatch_tab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	String.length
	.word	String.concat
	.word	String.substr


# Class Prototype
	.word	-1
Bar_protObj:
	.word	5
	.word	12
	.word	Bar_dispatch_tab
	.word	int_const2
	.word	0
	.word	0
	.word	0
	.word	int_const2
	.word	0
	.word	int_const2
	.word	int_const2
	.word	0
	.word	-1
Bazz_protObj:
	.word	2
	.word	6
	.word	Bazz_dispatch_tab
	.word	int_const2
	.word	0
	.word	0
	.word	-1
Bool_protObj:
	.word	7
	.word	4
	.word	Bool_dispatch_tab
	.word	0
	.word	-1
Foo_protObj:
	.word	3
	.word	8
	.word	Foo_dispatch_tab
	.word	int_const2
	.word	0
	.word	0
	.word	0
	.word	int_const2
	.word	-1
IO_protObj:
	.word	1
	.word	3
	.word	IO_dispatch_tab
	.word	-1
Int_protObj:
	.word	6
	.word	4
	.word	Int_dispatch_tab
	.word	0
	.word	-1
Main_protObj:
	.word	9
	.word	7
	.word	Main_dispatch_tab
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-1
Object_protObj:
	.word	0
	.word	3
	.word	Object_dispatch_tab
	.word	-1
Razz_protObj:
	.word	4
	.word	10
	.word	Razz_dispatch_tab
	.word	int_const2
	.word	0
	.word	0
	.word	0
	.word	int_const2
	.word	0
	.word	int_const2
	.word	-1
String_protObj:
	.word	8
	.word	5
	.word	String_dispatch_tab
	.word	int_const2
	.word	0

class_direct_parent_tab:
	.word	-1 #Object, tag_no:0, , tag_no:-1
	.word	0 #IO, tag_no:1, Object, tag_no:0
	.word	1 #Bazz, tag_no:2, IO, tag_no:1
	.word	2 #Foo, tag_no:3, Bazz, tag_no:2
	.word	3 #Razz, tag_no:4, Foo, tag_no:3
	.word	4 #Bar, tag_no:5, Razz, tag_no:4
	.word	0 #Int, tag_no:6, Object, tag_no:0
	.word	0 #Bool, tag_no:7, Object, tag_no:0
	.word	0 #String, tag_no:8, Object, tag_no:0
	.word	0 #Main, tag_no:9, Object, tag_no:0

class_prot_obj_tab:
	.word	Object_protObj
	.word	IO_protObj
	.word	Bazz_protObj
	.word	Foo_protObj
	.word	Razz_protObj
	.word	Bar_protObj
	.word	Int_protObj
	.word	Bool_protObj
	.word	String_protObj
	.word	Main_protObj

class_init_tab:
	.word	Object_init
	.word	IO_init
	.word	Bazz_init
	.word	Foo_init
	.word	Razz_init
	.word	Bar_init
	.word	Int_init
	.word	Bool_init
	.word	String_init
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
Bar_init:
	addiu	$sp	$sp	-12
	sw	$fp	12($sp)
	sw	$s0	8($sp)
	sw	$ra	4($sp)
	addiu	$fp	$sp	4
	move	$s0	$a0
	jal	Razz_init
# dispatch:doh
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label0
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label0:
	lw	$t1	8($a0)
	lw	$t1	32($t1)
	jalr	$t1
# dispatch:doh end
	sw	$a0	40($s0)
# dispatch:printh
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label1
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label1:
	lw	$t1	8($a0)
	lw	$t1	28($t1)
	jalr	$t1
# dispatch:printh end
	sw	$a0	44($s0)
	move	$a0	$s0
	lw	$fp	12($sp)
	lw	$s0	8($sp)
	lw	$ra	4($sp)
	addiu	$sp	$sp	12
	jr	$ra
Bazz_init:
	addiu	$sp	$sp	-16
	sw	$fp	16($sp)
	sw	$s0	12($sp)
	sw	$ra	8($sp)
	addiu	$fp	$sp	8
	move	$s0	$a0
	jal	IO_init
	la	$a0 int_const1
	sw	$a0	12($s0)
	move	$a0	$s0
	bne	$a0 $zero label2
	la	$a0 str_const0
	li	$t1 1
	jal	_case_abort2
label2:
	lw	$t1	0($a0)
# find ancestor
label7:
	li	$t2 2
	beq	$t1 $t2 label3
	li	$t2 4
	beq	$t1 $t2 label4
	li	$t2 3
	beq	$t1 $t2 label5
	li	$t2 5
	beq	$t1 $t2 label6
	li	$t2 0
	beq	$t1 $t2 label8
	la	$t2 class_direct_parent_tab
	li	$t3 4
	mul	$t1	$t1	$t3
	add	$t1	$t1	$t2
	lw	$t1	0($t1)
	b	label7
label8:
	jal	_case_abort
label3:
	sw	$a0	-4($fp)
	la	$a0 Foo_protObj
	jal	Object.copy
	jal	Foo_init
	b	label9
label4:
	sw	$a0	-4($fp)
	la	$a0 Bar_protObj
	jal	Object.copy
	jal	Bar_init
	b	label9
label5:
	sw	$a0	-4($fp)
	la	$a0 Razz_protObj
	jal	Object.copy
	jal	Razz_init
	b	label9
label6:
	sw	$a0	-4($fp)
	lw	$a0	-4($fp)
	b	label9
label9:
	sw	$a0	16($s0)
# dispatch:printh
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label10
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label10:
	lw	$t1	8($a0)
	lw	$t1	28($t1)
	jalr	$t1
# dispatch:printh end
	sw	$a0	20($s0)
	move	$a0	$s0
	lw	$fp	16($sp)
	lw	$s0	12($sp)
	lw	$ra	8($sp)
	addiu	$sp	$sp	16
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
Foo_init:
	addiu	$sp	$sp	-20
	sw	$fp	20($sp)
	sw	$s0	16($sp)
	sw	$ra	12($sp)
	addiu	$fp	$sp	12
	move	$s0	$a0
	jal	Bazz_init
	move	$a0	$s0
	bne	$a0 $zero label11
	la	$a0 str_const0
	li	$t1 1
	jal	_case_abort2
label11:
	lw	$t1	0($a0)
# find ancestor
label15:
	li	$t2 4
	beq	$t1 $t2 label12
	li	$t2 3
	beq	$t1 $t2 label13
	li	$t2 5
	beq	$t1 $t2 label14
	li	$t2 0
	beq	$t1 $t2 label16
	la	$t2 class_direct_parent_tab
	li	$t3 4
	mul	$t1	$t1	$t3
	add	$t1	$t1	$t2
	lw	$t1	0($t1)
	b	label15
label16:
	jal	_case_abort
label12:
	sw	$a0	-4($fp)
	la	$a0 Bar_protObj
	jal	Object.copy
	jal	Bar_init
	b	label17
label13:
	sw	$a0	-4($fp)
	la	$a0 Razz_protObj
	jal	Object.copy
	jal	Razz_init
	b	label17
label14:
	sw	$a0	-4($fp)
	lw	$a0	-4($fp)
	b	label17
label17:
	sw	$a0	24($s0)
# dispatch:doh
# evaluate dispatch expr
	lw	$a0	24($s0)
	bne	$a0 $zero label18
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label18:
	lw	$t1	8($a0)
	lw	$t1	32($t1)
	jalr	$t1
# dispatch:doh end
	sw	$a0	-4($fp)
# dispatch:doh
# evaluate dispatch expr
	lw	$a0	16($s0)
	bne	$a0 $zero label19
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label19:
	lw	$t1	8($a0)
	lw	$t1	32($t1)
	jalr	$t1
# dispatch:doh end
	sw	$a0	-8($fp)
	la	$a0 Int_protObj
	jal	Object.copy
	jal	Int_init
	lw	$t1	-4($fp)
	lw	$t1	12($t1)
	lw	$t2	-8($fp)
	lw	$t2	12($t2)
	add	$t1	$t1	$t2
	sw	$t1	12($a0)
	sw	$a0	-4($fp)
# dispatch:doh
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label20
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label20:
	lw	$t1	8($a0)
	lw	$t1	32($t1)
	jalr	$t1
# dispatch:doh end
	sw	$a0	-8($fp)
	la	$a0 Int_protObj
	jal	Object.copy
	jal	Int_init
	lw	$t1	-4($fp)
	lw	$t1	12($t1)
	lw	$t2	-8($fp)
	lw	$t2	12($t2)
	add	$t1	$t1	$t2
	sw	$t1	12($a0)
	sw	$a0	-4($fp)
# dispatch:printh
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label21
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label21:
	lw	$t1	8($a0)
	lw	$t1	28($t1)
	jalr	$t1
# dispatch:printh end
	sw	$a0	-8($fp)
	la	$a0 Int_protObj
	jal	Object.copy
	jal	Int_init
	lw	$t1	-4($fp)
	lw	$t1	12($t1)
	lw	$t2	-8($fp)
	lw	$t2	12($t2)
	add	$t1	$t1	$t2
	sw	$t1	12($a0)
	sw	$a0	28($s0)
	move	$a0	$s0
	lw	$fp	20($sp)
	lw	$s0	16($sp)
	lw	$ra	12($sp)
	addiu	$sp	$sp	20
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
	la	$a0 Bazz_protObj
	jal	Object.copy
	jal	Bazz_init
	sw	$a0	12($s0)
	la	$a0 Foo_protObj
	jal	Object.copy
	jal	Foo_init
	sw	$a0	16($s0)
	la	$a0 Razz_protObj
	jal	Object.copy
	jal	Razz_init
	sw	$a0	20($s0)
	la	$a0 Bar_protObj
	jal	Object.copy
	jal	Bar_init
	sw	$a0	24($s0)
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
Razz_init:
	addiu	$sp	$sp	-20
	sw	$fp	20($sp)
	sw	$s0	16($sp)
	sw	$ra	12($sp)
	addiu	$fp	$sp	12
	move	$s0	$a0
	jal	Foo_init
	move	$a0	$s0
	bne	$a0 $zero label22
	la	$a0 str_const0
	li	$t1 1
	jal	_case_abort2
label22:
	lw	$t1	0($a0)
# find ancestor
label25:
	li	$t2 4
	beq	$t1 $t2 label23
	li	$t2 5
	beq	$t1 $t2 label24
	li	$t2 0
	beq	$t1 $t2 label26
	la	$t2 class_direct_parent_tab
	li	$t3 4
	mul	$t1	$t1	$t3
	add	$t1	$t1	$t2
	lw	$t1	0($t1)
	b	label25
label26:
	jal	_case_abort
label23:
	sw	$a0	-4($fp)
	la	$a0 Bar_protObj
	jal	Object.copy
	jal	Bar_init
	b	label27
label24:
	sw	$a0	-4($fp)
	lw	$a0	-4($fp)
	b	label27
label27:
	sw	$a0	32($s0)
	lw	$a0	24($s0)
	bne	$a0 $zero label28
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label28:
	jal	Bazz.doh
	sw	$a0	-4($fp)
# dispatch:doh
# evaluate dispatch expr
	lw	$a0	16($s0)
	bne	$a0 $zero label29
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label29:
	lw	$t1	8($a0)
	lw	$t1	32($t1)
	jalr	$t1
# dispatch:doh end
	sw	$a0	-8($fp)
	la	$a0 Int_protObj
	jal	Object.copy
	jal	Int_init
	lw	$t1	-4($fp)
	lw	$t1	12($t1)
	lw	$t2	-8($fp)
	lw	$t2	12($t2)
	add	$t1	$t1	$t2
	sw	$t1	12($a0)
	sw	$a0	-4($fp)
# dispatch:doh
# evaluate dispatch expr
	lw	$a0	32($s0)
	bne	$a0 $zero label30
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label30:
	lw	$t1	8($a0)
	lw	$t1	32($t1)
	jalr	$t1
# dispatch:doh end
	sw	$a0	-8($fp)
	la	$a0 Int_protObj
	jal	Object.copy
	jal	Int_init
	lw	$t1	-4($fp)
	lw	$t1	12($t1)
	lw	$t2	-8($fp)
	lw	$t2	12($t2)
	add	$t1	$t1	$t2
	sw	$t1	12($a0)
	sw	$a0	-4($fp)
# dispatch:doh
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label31
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label31:
	lw	$t1	8($a0)
	lw	$t1	32($t1)
	jalr	$t1
# dispatch:doh end
	sw	$a0	-8($fp)
	la	$a0 Int_protObj
	jal	Object.copy
	jal	Int_init
	lw	$t1	-4($fp)
	lw	$t1	12($t1)
	lw	$t2	-8($fp)
	lw	$t2	12($t2)
	add	$t1	$t1	$t2
	sw	$t1	12($a0)
	sw	$a0	-4($fp)
# dispatch:printh
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label32
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label32:
	lw	$t1	8($a0)
	lw	$t1	28($t1)
	jalr	$t1
# dispatch:printh end
	sw	$a0	-8($fp)
	la	$a0 Int_protObj
	jal	Object.copy
	jal	Int_init
	lw	$t1	-4($fp)
	lw	$t1	12($t1)
	lw	$t2	-8($fp)
	lw	$t2	12($t2)
	add	$t1	$t1	$t2
	sw	$t1	12($a0)
	sw	$a0	36($s0)
	move	$a0	$s0
	lw	$fp	20($sp)
	lw	$s0	16($sp)
	lw	$ra	12($sp)
	addiu	$sp	$sp	20
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

Bazz.printh:
	addiu	$sp	$sp	-12
	sw	$fp	12($sp)
	sw	$s0	8($sp)
	sw	$ra	4($sp)
	addiu	$fp	$sp	4
	move	$s0	$a0
# dispatch:out_int
# push arg :0
	lw	$a0	12($s0)
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label33
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label33:
	lw	$t1	8($a0)
	lw	$t1	16($t1)
	jalr	$t1
# dispatch:out_int end
	la	$a0 int_const2
	lw	$fp	12($sp)
	lw	$s0	8($sp)
	lw	$ra	4($sp)
	addiu	$sp	$sp	12
	addiu	$sp	$sp	0
	jr	$ra

Bazz.doh:
	addiu	$sp	$sp	-24
	sw	$fp	24($sp)
	sw	$s0	20($sp)
	sw	$ra	16($sp)
	addiu	$fp	$sp	16
	move	$s0	$a0
	lw	$a0	12($s0)
	sw	$a0	-4($fp)
	lw	$a0	12($s0)
	sw	$a0	-8($fp)
	la	$a0 int_const1
	sw	$a0	-12($fp)
	la	$a0 Int_protObj
	jal	Object.copy
	jal	Int_init
	lw	$t1	-8($fp)
	lw	$t1	12($t1)
	lw	$t2	-12($fp)
	lw	$t2	12($t2)
	add	$t1	$t1	$t2
	sw	$t1	12($a0)
	sw	$a0	12($s0)
	lw	$a0	-4($fp)
	lw	$fp	24($sp)
	lw	$s0	20($sp)
	lw	$ra	16($sp)
	addiu	$sp	$sp	24
	addiu	$sp	$sp	0
	jr	$ra

Foo.doh:
	addiu	$sp	$sp	-24
	sw	$fp	24($sp)
	sw	$s0	20($sp)
	sw	$ra	16($sp)
	addiu	$fp	$sp	16
	move	$s0	$a0
	lw	$a0	12($s0)
	sw	$a0	-4($fp)
	lw	$a0	12($s0)
	sw	$a0	-8($fp)
	la	$a0 int_const0
	sw	$a0	-12($fp)
	la	$a0 Int_protObj
	jal	Object.copy
	jal	Int_init
	lw	$t1	-8($fp)
	lw	$t1	12($t1)
	lw	$t2	-12($fp)
	lw	$t2	12($t2)
	add	$t1	$t1	$t2
	sw	$t1	12($a0)
	sw	$a0	12($s0)
	lw	$a0	-4($fp)
	lw	$fp	24($sp)
	lw	$s0	20($sp)
	lw	$ra	16($sp)
	addiu	$sp	$sp	24
	addiu	$sp	$sp	0
	jr	$ra

Main.main:
	addiu	$sp	$sp	-12
	sw	$fp	12($sp)
	sw	$s0	8($sp)
	sw	$ra	4($sp)
	addiu	$fp	$sp	4
	move	$s0	$a0
	la	$a0 str_const1
	lw	$fp	12($sp)
	lw	$s0	8($sp)
	lw	$ra	4($sp)
	addiu	$sp	$sp	12
	addiu	$sp	$sp	0
	jr	$ra


# end of generated code

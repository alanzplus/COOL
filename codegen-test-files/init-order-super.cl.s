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
	.word	4
_bool_tag:
	.word	5
_string_tag:
	.word	6

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
	.word	6
	.word	5
	.word	String_dispatch_tab
	.word	int_const5
	.byte	0	
	.align	2
	.word	-1
str_const12:
	.word	6
	.word	6
	.word	String_dispatch_tab
	.word	int_const3
	.ascii	"Main"
	.byte	0	
	.align	2
	.word	-1
str_const11:
	.word	6
	.word	6
	.word	String_dispatch_tab
	.word	int_const3
	.ascii	"Base"
	.byte	0	
	.align	2
	.word	-1
str_const10:
	.word	6
	.word	6
	.word	String_dispatch_tab
	.word	int_const6
	.ascii	"String"
	.byte	0	
	.align	2
	.word	-1
str_const9:
	.word	6
	.word	6
	.word	String_dispatch_tab
	.word	int_const3
	.ascii	"Bool"
	.byte	0	
	.align	2
	.word	-1
str_const8:
	.word	6
	.word	5
	.word	String_dispatch_tab
	.word	int_const2
	.ascii	"Int"
	.byte	0	
	.align	2
	.word	-1
str_const7:
	.word	6
	.word	5
	.word	String_dispatch_tab
	.word	int_const1
	.ascii	"IO"
	.byte	0	
	.align	2
	.word	-1
str_const6:
	.word	6
	.word	6
	.word	String_dispatch_tab
	.word	int_const6
	.ascii	"Object"
	.byte	0	
	.align	2
	.word	-1
str_const5:
	.word	6
	.word	7
	.word	String_dispatch_tab
	.word	int_const7
	.ascii	"_prim_slot"
	.byte	0	
	.align	2
	.word	-1
str_const4:
	.word	6
	.word	7
	.word	String_dispatch_tab
	.word	int_const8
	.ascii	"SELF_TYPE"
	.byte	0	
	.align	2
	.word	-1
str_const3:
	.word	6
	.word	7
	.word	String_dispatch_tab
	.word	int_const8
	.ascii	"_no_class"
	.byte	0	
	.align	2
	.word	-1
str_const2:
	.word	6
	.word	8
	.word	String_dispatch_tab
	.word	int_const9
	.ascii	"<basic class>"
	.byte	0	
	.align	2
	.word	-1
str_const1:
	.word	6
	.word	5
	.word	String_dispatch_tab
	.word	int_const0
	.ascii	"\n"
	.byte	0	
	.align	2
	.word	-1
str_const0:
	.word	6
	.word	10
	.word	String_dispatch_tab
	.word	int_const10
	.ascii	"./init-order-super.cl"
	.byte	0	
	.align	2
	.word	-1
int_const10:
	.word	4
	.word	4
	.word	Int_dispatch_tab
	.word	21
	.word	-1
int_const9:
	.word	4
	.word	4
	.word	Int_dispatch_tab
	.word	13
	.word	-1
int_const8:
	.word	4
	.word	4
	.word	Int_dispatch_tab
	.word	9
	.word	-1
int_const7:
	.word	4
	.word	4
	.word	Int_dispatch_tab
	.word	10
	.word	-1
int_const6:
	.word	4
	.word	4
	.word	Int_dispatch_tab
	.word	6
	.word	-1
int_const5:
	.word	4
	.word	4
	.word	Int_dispatch_tab
	.word	0
	.word	-1
int_const4:
	.word	4
	.word	4
	.word	Int_dispatch_tab
	.word	5
	.word	-1
int_const3:
	.word	4
	.word	4
	.word	Int_dispatch_tab
	.word	4
	.word	-1
int_const2:
	.word	4
	.word	4
	.word	Int_dispatch_tab
	.word	3
	.word	-1
int_const1:
	.word	4
	.word	4
	.word	Int_dispatch_tab
	.word	2
	.word	-1
int_const0:
	.word	4
	.word	4
	.word	Int_dispatch_tab
	.word	1
	.word	-1
bool_const0:
	.word	5
	.word	4
	.word	Bool_dispatch_tab
	.word	0
	.word	-1
bool_const1:
	.word	5
	.word	4
	.word	Bool_dispatch_tab
	.word	1

# Declare Class Tag
	.globl	_Base_tag
	.globl	_IO_tag
	.globl	_Main_tag
	.globl	_Object_tag

# Class Tag Definition
_Base_tag:
	.word	2
_IO_tag:
	.word	1
_Main_tag:
	.word	3
_Object_tag:
	.word	0

# Class Name String Table
class_nameTab:
	.word	str_const6
	.word	str_const7
	.word	str_const11
	.word	str_const12
	.word	str_const8
	.word	str_const9
	.word	str_const10

# Class Dispatch Table
Base_dispatch_tab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Base.recite

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
	.word	Base.recite
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
Base_protObj:
	.word	2
	.word	5
	.word	Base_dispatch_tab
	.word	0
	.word	0
	.word	-1
Bool_protObj:
	.word	5
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
	.word	4
	.word	4
	.word	Int_dispatch_tab
	.word	0
	.word	-1
Main_protObj:
	.word	3
	.word	8
	.word	Main_dispatch_tab
	.word	0
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
String_protObj:
	.word	6
	.word	5
	.word	String_dispatch_tab
	.word	int_const5
	.word	0

class_direct_parent_tab:
	.word	-1 #Object, tag_no:0, , tag_no:-1
	.word	0 #IO, tag_no:1, Object, tag_no:0
	.word	1 #Base, tag_no:2, IO, tag_no:1
	.word	2 #Main, tag_no:3, Base, tag_no:2
	.word	0 #Int, tag_no:4, Object, tag_no:0
	.word	0 #Bool, tag_no:5, Object, tag_no:0
	.word	0 #String, tag_no:6, Object, tag_no:0

class_prot_obj_tab:
	.word	Object_protObj
	.word	IO_protObj
	.word	Base_protObj
	.word	Main_protObj
	.word	Int_protObj
	.word	Bool_protObj
	.word	String_protObj

class_init_tab:
	.word	Object_init
	.word	IO_init
	.word	Base_init
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
Base_init:
	addiu	$sp	$sp	-12
	sw	$fp	12($sp)
	sw	$s0	8($sp)
	sw	$ra	4($sp)
	addiu	$fp	$sp	4
	move	$s0	$a0
	jal	IO_init
# dispatch:recite
# push arg :0
	la	$a0 int_const0
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label0
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label0:
	lw	$t1	8($a0)
	lw	$t1	28($t1)
	jalr	$t1
# dispatch:recite end
	sw	$a0	12($s0)
# dispatch:recite
# push arg :0
	la	$a0 int_const1
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
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
# dispatch:recite end
	sw	$a0	16($s0)
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
	jal	Base_init
# dispatch:recite
# push arg :0
	la	$a0 int_const2
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label2
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label2:
	lw	$t1	8($a0)
	lw	$t1	28($t1)
	jalr	$t1
# dispatch:recite end
	sw	$a0	20($s0)
# dispatch:recite
# push arg :0
	la	$a0 int_const3
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label3
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label3:
	lw	$t1	8($a0)
	lw	$t1	28($t1)
	jalr	$t1
# dispatch:recite end
	sw	$a0	24($s0)
# dispatch:recite
# push arg :0
	la	$a0 int_const4
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label4
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label4:
	lw	$t1	8($a0)
	lw	$t1	28($t1)
	jalr	$t1
# dispatch:recite end
	sw	$a0	28($s0)
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

Base.recite:
	addiu	$sp	$sp	-12
	sw	$fp	12($sp)
	sw	$s0	8($sp)
	sw	$ra	4($sp)
	addiu	$fp	$sp	4
	move	$s0	$a0
# dispatch:out_int
# push arg :0
	lw	$a0	12($fp)
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label5
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label5:
	lw	$t1	8($a0)
	lw	$t1	16($t1)
	jalr	$t1
# dispatch:out_int end
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
	move	$a0	$s0
	lw	$fp	12($sp)
	lw	$s0	8($sp)
	lw	$ra	4($sp)
	addiu	$sp	$sp	12
	addiu	$sp	$sp	4
	jr	$ra

Main.main:
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
	addiu	$sp	$sp	0
	jr	$ra


# end of generated code

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
str_const11:
	.word	4
	.word	5
	.word	String_dispatch_tab
	.word	int_const0
	.byte	0	
	.align	2
	.word	-1
str_const10:
	.word	4
	.word	6
	.word	String_dispatch_tab
	.word	int_const3
	.ascii	"Main"
	.byte	0	
	.align	2
	.word	-1
str_const9:
	.word	4
	.word	6
	.word	String_dispatch_tab
	.word	int_const4
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
	.word	int_const5
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
	.word	int_const4
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
	.word	7
	.word	String_dispatch_tab
	.word	int_const10
	.ascii	"./not.cl"
	.byte	0	
	.align	2
	.word	-1
int_const10:
	.word	2
	.word	4
	.word	Int_dispatch_tab
	.word	8
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
	.word	3
	.word	-1
int_const4:
	.word	2
	.word	4
	.word	Int_dispatch_tab
	.word	6
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
	.word	1
	.word	-1
int_const1:
	.word	2
	.word	4
	.word	Int_dispatch_tab
	.word	100
	.word	-1
int_const0:
	.word	2
	.word	4
	.word	Int_dispatch_tab
	.word	0
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
	.globl	_IO_tag
	.globl	_Main_tag
	.globl	_Object_tag

# Class Tag Definition
_IO_tag:
	.word	1
_Main_tag:
	.word	5
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
	.word	5
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
	.word	int_const0
	.word	0

class_direct_parent_tab:
	.word	-1 #Object, tag_no:0, , tag_no:-1
	.word	0 #IO, tag_no:1, Object, tag_no:0
	.word	0 #Int, tag_no:2, Object, tag_no:0
	.word	0 #Bool, tag_no:3, Object, tag_no:0
	.word	0 #String, tag_no:4, Object, tag_no:0
	.word	0 #Main, tag_no:5, Object, tag_no:0

class_prot_obj_tab:
	.word	Object_protObj
	.word	IO_protObj
	.word	Int_protObj
	.word	Bool_protObj
	.word	String_protObj
	.word	Main_protObj

class_init_tab:
	.word	Object_init
	.word	IO_init
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

Main.main:
	addiu	$sp	$sp	-28
	sw	$fp	28($sp)
	sw	$s0	24($sp)
	sw	$ra	20($sp)
	addiu	$fp	$sp	20
	move	$s0	$a0
	la	$a0 int_const0
	sw	$a0	-4($fp)
	la	$a0	bool_const0
	sw	$a0	-8($fp)
# loop class
label0:
	lw	$a0	-4($fp)
	sw	$a0	-12($fp)
	la	$a0 int_const1
	sw	$a0	-16($fp)
	la	$a0	bool_const1
	lw	$t1	-12($fp)
	lw	$t1	12($t1)
	lw	$t2	-16($fp)
	lw	$t2	12($t2)
	blt	$t1 $t2 label2
	la	$a0	bool_const0
label2:
	lw	$t1	12($a0)
	beqz	$t1 label1
	lw	$a0	-8($fp)
	sw	$a0	-12($fp)
	lw	$a0	-8($fp)
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label3
	la	$a0	bool_const0
label3:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label4
	la	$a0	bool_const0
label4:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label5
	la	$a0	bool_const0
label5:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label6
	la	$a0	bool_const0
label6:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label7
	la	$a0	bool_const0
label7:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label8
	la	$a0	bool_const0
label8:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label9
	la	$a0	bool_const0
label9:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label10
	la	$a0	bool_const0
label10:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label11
	la	$a0	bool_const0
label11:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label12
	la	$a0	bool_const0
label12:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label13
	la	$a0	bool_const0
label13:
	sw	$a0	-16($fp)
	la	$a0	bool_const1
	lw	$t1	-12($fp)
	lw	$t2	-16($fp)
	beq	$t1 $t2 label14
	la	$a1	bool_const0
	jal	equality_test
label14:
	lw	$a0	-8($fp)
	sw	$a0	-12($fp)
	lw	$a0	-8($fp)
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label15
	la	$a0	bool_const0
label15:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label16
	la	$a0	bool_const0
label16:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label17
	la	$a0	bool_const0
label17:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label18
	la	$a0	bool_const0
label18:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label19
	la	$a0	bool_const0
label19:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label20
	la	$a0	bool_const0
label20:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label21
	la	$a0	bool_const0
label21:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label22
	la	$a0	bool_const0
label22:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label23
	la	$a0	bool_const0
label23:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label24
	la	$a0	bool_const0
label24:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label25
	la	$a0	bool_const0
label25:
	sw	$a0	-16($fp)
	la	$a0	bool_const1
	lw	$t1	-12($fp)
	lw	$t2	-16($fp)
	beq	$t1 $t2 label26
	la	$a1	bool_const0
	jal	equality_test
label26:
	lw	$a0	-8($fp)
	sw	$a0	-12($fp)
	lw	$a0	-8($fp)
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label27
	la	$a0	bool_const0
label27:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label28
	la	$a0	bool_const0
label28:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label29
	la	$a0	bool_const0
label29:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label30
	la	$a0	bool_const0
label30:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label31
	la	$a0	bool_const0
label31:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label32
	la	$a0	bool_const0
label32:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label33
	la	$a0	bool_const0
label33:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label34
	la	$a0	bool_const0
label34:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label35
	la	$a0	bool_const0
label35:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label36
	la	$a0	bool_const0
label36:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label37
	la	$a0	bool_const0
label37:
	sw	$a0	-16($fp)
	la	$a0	bool_const1
	lw	$t1	-12($fp)
	lw	$t2	-16($fp)
	beq	$t1 $t2 label38
	la	$a1	bool_const0
	jal	equality_test
label38:
	lw	$a0	-8($fp)
	sw	$a0	-12($fp)
	lw	$a0	-8($fp)
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label39
	la	$a0	bool_const0
label39:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label40
	la	$a0	bool_const0
label40:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label41
	la	$a0	bool_const0
label41:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label42
	la	$a0	bool_const0
label42:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label43
	la	$a0	bool_const0
label43:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label44
	la	$a0	bool_const0
label44:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label45
	la	$a0	bool_const0
label45:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label46
	la	$a0	bool_const0
label46:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label47
	la	$a0	bool_const0
label47:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label48
	la	$a0	bool_const0
label48:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label49
	la	$a0	bool_const0
label49:
	sw	$a0	-16($fp)
	la	$a0	bool_const1
	lw	$t1	-12($fp)
	lw	$t2	-16($fp)
	beq	$t1 $t2 label50
	la	$a1	bool_const0
	jal	equality_test
label50:
	lw	$a0	-8($fp)
	sw	$a0	-12($fp)
	lw	$a0	-8($fp)
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label51
	la	$a0	bool_const0
label51:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label52
	la	$a0	bool_const0
label52:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label53
	la	$a0	bool_const0
label53:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label54
	la	$a0	bool_const0
label54:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label55
	la	$a0	bool_const0
label55:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label56
	la	$a0	bool_const0
label56:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label57
	la	$a0	bool_const0
label57:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label58
	la	$a0	bool_const0
label58:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label59
	la	$a0	bool_const0
label59:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label60
	la	$a0	bool_const0
label60:
	lw	$t1	12($a0)
	la	$a0	bool_const1
	beqz	$t1 label61
	la	$a0	bool_const0
label61:
	sw	$a0	-16($fp)
	la	$a0	bool_const1
	lw	$t1	-12($fp)
	lw	$t2	-16($fp)
	beq	$t1 $t2 label62
	la	$a1	bool_const0
	jal	equality_test
label62:
	lw	$a0	-4($fp)
	sw	$a0	-12($fp)
	la	$a0 int_const2
	sw	$a0	-16($fp)
	la	$a0 Int_protObj
	jal	Object.copy
	jal	Int_init
	lw	$t1	-12($fp)
	lw	$t1	12($t1)
	lw	$t2	-16($fp)
	lw	$t2	12($t2)
	add	$t1	$t1	$t2
	sw	$t1	12($a0)
	sw	$a0	-4($fp)
	b	label0
label1:
	li	$a0 0
# loop class end
	lw	$a0	-8($fp)
	lw	$t1	12($a0)
	beqz	$t1 label63
# dispatch:abort
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label65
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label65:
	lw	$t1	8($a0)
	lw	$t1	0($t1)
	jalr	$t1
# dispatch:abort end
	b	label64
label63:
	la	$a0 int_const0
label64:
	lw	$fp	28($sp)
	lw	$s0	24($sp)
	lw	$ra	20($sp)
	addiu	$sp	$sp	28
	addiu	$sp	$sp	0
	jr	$ra


# end of generated code

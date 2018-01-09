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
str_const16:
	.word	5
	.word	5
	.word	String_dispatch_tab
	.word	int_const1
	.byte	0	
	.align	2
	.word	-1
str_const15:
	.word	5
	.word	6
	.word	String_dispatch_tab
	.word	int_const3
	.ascii	"Main"
	.byte	0	
	.align	2
	.word	-1
str_const14:
	.word	5
	.word	9
	.word	String_dispatch_tab
	.word	int_const4
	.ascii	"CellularAutomaton"
	.byte	0	
	.align	2
	.word	-1
str_const13:
	.word	5
	.word	6
	.word	String_dispatch_tab
	.word	int_const5
	.ascii	"String"
	.byte	0	
	.align	2
	.word	-1
str_const12:
	.word	5
	.word	6
	.word	String_dispatch_tab
	.word	int_const3
	.ascii	"Bool"
	.byte	0	
	.align	2
	.word	-1
str_const11:
	.word	5
	.word	5
	.word	String_dispatch_tab
	.word	int_const6
	.ascii	"Int"
	.byte	0	
	.align	2
	.word	-1
str_const10:
	.word	5
	.word	5
	.word	String_dispatch_tab
	.word	int_const7
	.ascii	"IO"
	.byte	0	
	.align	2
	.word	-1
str_const9:
	.word	5
	.word	6
	.word	String_dispatch_tab
	.word	int_const5
	.ascii	"Object"
	.byte	0	
	.align	2
	.word	-1
str_const8:
	.word	5
	.word	7
	.word	String_dispatch_tab
	.word	int_const8
	.ascii	"_prim_slot"
	.byte	0	
	.align	2
	.word	-1
str_const7:
	.word	5
	.word	7
	.word	String_dispatch_tab
	.word	int_const9
	.ascii	"SELF_TYPE"
	.byte	0	
	.align	2
	.word	-1
str_const6:
	.word	5
	.word	7
	.word	String_dispatch_tab
	.word	int_const9
	.ascii	"_no_class"
	.byte	0	
	.align	2
	.word	-1
str_const5:
	.word	5
	.word	8
	.word	String_dispatch_tab
	.word	int_const10
	.ascii	"<basic class>"
	.byte	0	
	.align	2
	.word	-1
str_const4:
	.word	5
	.word	9
	.word	String_dispatch_tab
	.word	int_const11
	.ascii	"         X         "
	.byte	0	
	.align	2
	.word	-1
str_const3:
	.word	5
	.word	5
	.word	String_dispatch_tab
	.word	int_const0
	.ascii	"."
	.byte	0	
	.align	2
	.word	-1
str_const2:
	.word	5
	.word	5
	.word	String_dispatch_tab
	.word	int_const0
	.ascii	"X"
	.byte	0	
	.align	2
	.word	-1
str_const1:
	.word	5
	.word	5
	.word	String_dispatch_tab
	.word	int_const0
	.ascii	"\n"
	.byte	0	
	.align	2
	.word	-1
str_const0:
	.word	5
	.word	7
	.word	String_dispatch_tab
	.word	int_const8
	.ascii	"./cells.cl"
	.byte	0	
	.align	2
	.word	-1
int_const11:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	19
	.word	-1
int_const10:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	13
	.word	-1
int_const9:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	9
	.word	-1
int_const8:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	10
	.word	-1
int_const7:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	2
	.word	-1
int_const6:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	3
	.word	-1
int_const5:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	6
	.word	-1
int_const4:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	17
	.word	-1
int_const3:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	4
	.word	-1
int_const2:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	20
	.word	-1
int_const1:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	0
	.word	-1
int_const0:
	.word	3
	.word	4
	.word	Int_dispatch_tab
	.word	1
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
	.globl	_CellularAutomaton_tag
	.globl	_IO_tag
	.globl	_Main_tag
	.globl	_Object_tag

# Class Tag Definition
_CellularAutomaton_tag:
	.word	2
_IO_tag:
	.word	1
_Main_tag:
	.word	6
_Object_tag:
	.word	0

# Class Name String Table
class_nameTab:
	.word	str_const9
	.word	str_const10
	.word	str_const14
	.word	str_const11
	.word	str_const12
	.word	str_const13
	.word	str_const15

# Class Dispatch Table
Bool_dispatch_tab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy

CellularAutomaton_dispatch_tab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	CellularAutomaton.init
	.word	CellularAutomaton.print
	.word	CellularAutomaton.num_cells
	.word	CellularAutomaton.cell
	.word	CellularAutomaton.cell_left_neighbor
	.word	CellularAutomaton.cell_right_neighbor
	.word	CellularAutomaton.cell_at_next_evolution
	.word	CellularAutomaton.evolve

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
	.word	4
	.word	4
	.word	Bool_dispatch_tab
	.word	0
	.word	-1
CellularAutomaton_protObj:
	.word	2
	.word	4
	.word	CellularAutomaton_dispatch_tab
	.word	str_const16
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
	.word	6
	.word	4
	.word	Main_dispatch_tab
	.word	0
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
	.word	int_const1
	.word	0

class_direct_parent_tab:
	.word	-1 #Object, tag_no:0, , tag_no:-1
	.word	0 #IO, tag_no:1, Object, tag_no:0
	.word	1 #CellularAutomaton, tag_no:2, IO, tag_no:1
	.word	0 #Int, tag_no:3, Object, tag_no:0
	.word	0 #Bool, tag_no:4, Object, tag_no:0
	.word	0 #String, tag_no:5, Object, tag_no:0
	.word	0 #Main, tag_no:6, Object, tag_no:0

class_prot_obj_tab:
	.word	Object_protObj
	.word	IO_protObj
	.word	CellularAutomaton_protObj
	.word	Int_protObj
	.word	Bool_protObj
	.word	String_protObj
	.word	Main_protObj

class_init_tab:
	.word	Object_init
	.word	IO_init
	.word	CellularAutomaton_init
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
CellularAutomaton_init:
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

CellularAutomaton.init:
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

CellularAutomaton.print:
	addiu	$sp	$sp	-12
	sw	$fp	12($sp)
	sw	$s0	8($sp)
	sw	$ra	4($sp)
	addiu	$fp	$sp	4
	move	$s0	$a0
# dispatch:out_string
# push arg :0
# dispatch:concat
# push arg :0
	la	$a0 str_const1
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# evaluate dispatch expr
	lw	$a0	12($s0)
	bne	$a0 $zero label0
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label0:
	lw	$t1	8($a0)
	lw	$t1	16($t1)
	jalr	$t1
# dispatch:concat end
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
	lw	$t1	12($t1)
	jalr	$t1
# dispatch:out_string end
	move	$a0	$s0
	lw	$fp	12($sp)
	lw	$s0	8($sp)
	lw	$ra	4($sp)
	addiu	$sp	$sp	12
	addiu	$sp	$sp	0
	jr	$ra

CellularAutomaton.num_cells:
	addiu	$sp	$sp	-12
	sw	$fp	12($sp)
	sw	$s0	8($sp)
	sw	$ra	4($sp)
	addiu	$fp	$sp	4
	move	$s0	$a0
# dispatch:length
# evaluate dispatch expr
	lw	$a0	12($s0)
	bne	$a0 $zero label2
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label2:
	lw	$t1	8($a0)
	lw	$t1	12($t1)
	jalr	$t1
# dispatch:length end
	lw	$fp	12($sp)
	lw	$s0	8($sp)
	lw	$ra	4($sp)
	addiu	$sp	$sp	12
	addiu	$sp	$sp	0
	jr	$ra

CellularAutomaton.cell:
	addiu	$sp	$sp	-12
	sw	$fp	12($sp)
	sw	$s0	8($sp)
	sw	$ra	4($sp)
	addiu	$fp	$sp	4
	move	$s0	$a0
# dispatch:substr
# push arg :0
	lw	$a0	12($fp)
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# push arg :1
	la	$a0 int_const0
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# evaluate dispatch expr
	lw	$a0	12($s0)
	bne	$a0 $zero label3
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label3:
	lw	$t1	8($a0)
	lw	$t1	20($t1)
	jalr	$t1
# dispatch:substr end
	lw	$fp	12($sp)
	lw	$s0	8($sp)
	lw	$ra	4($sp)
	addiu	$sp	$sp	12
	addiu	$sp	$sp	4
	jr	$ra

CellularAutomaton.cell_left_neighbor:
	addiu	$sp	$sp	-20
	sw	$fp	20($sp)
	sw	$s0	16($sp)
	sw	$ra	12($sp)
	addiu	$fp	$sp	12
	move	$s0	$a0
	lw	$a0	12($fp)
	sw	$a0	-4($fp)
	la	$a0 int_const1
	sw	$a0	-8($fp)
	la	$a0	bool_const1
	lw	$t1	-4($fp)
	lw	$t2	-8($fp)
	beq	$t1 $t2 label4
	la	$a1	bool_const0
	jal	equality_test
label4:
	lw	$t1	12($a0)
	beqz	$t1 label5
# dispatch:cell
# push arg :0
# dispatch:num_cells
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label7
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label7:
	lw	$t1	8($a0)
	lw	$t1	36($t1)
	jalr	$t1
# dispatch:num_cells end
	sw	$a0	-4($fp)
	la	$a0 int_const0
	sw	$a0	-8($fp)
	la	$a0 Int_protObj
	jal	Object.copy
	jal	Int_init
	lw	$t1	-4($fp)
	lw	$t1	12($t1)
	lw	$t2	-8($fp)
	lw	$t2	12($t2)
	sub	$t1	$t1	$t2
	sw	$t1	12($a0)
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label8
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label8:
	lw	$t1	8($a0)
	lw	$t1	40($t1)
	jalr	$t1
# dispatch:cell end
	b	label6
label5:
# dispatch:cell
# push arg :0
	lw	$a0	12($fp)
	sw	$a0	-4($fp)
	la	$a0 int_const0
	sw	$a0	-8($fp)
	la	$a0 Int_protObj
	jal	Object.copy
	jal	Int_init
	lw	$t1	-4($fp)
	lw	$t1	12($t1)
	lw	$t2	-8($fp)
	lw	$t2	12($t2)
	sub	$t1	$t1	$t2
	sw	$t1	12($a0)
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label9
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label9:
	lw	$t1	8($a0)
	lw	$t1	40($t1)
	jalr	$t1
# dispatch:cell end
label6:
	lw	$fp	20($sp)
	lw	$s0	16($sp)
	lw	$ra	12($sp)
	addiu	$sp	$sp	20
	addiu	$sp	$sp	4
	jr	$ra

CellularAutomaton.cell_right_neighbor:
	addiu	$sp	$sp	-28
	sw	$fp	28($sp)
	sw	$s0	24($sp)
	sw	$ra	20($sp)
	addiu	$fp	$sp	20
	move	$s0	$a0
	lw	$a0	12($fp)
	sw	$a0	-4($fp)
# dispatch:num_cells
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label10
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label10:
	lw	$t1	8($a0)
	lw	$t1	36($t1)
	jalr	$t1
# dispatch:num_cells end
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
	sub	$t1	$t1	$t2
	sw	$t1	12($a0)
	sw	$a0	-8($fp)
	la	$a0	bool_const1
	lw	$t1	-4($fp)
	lw	$t2	-8($fp)
	beq	$t1 $t2 label11
	la	$a1	bool_const0
	jal	equality_test
label11:
	lw	$t1	12($a0)
	beqz	$t1 label12
# dispatch:cell
# push arg :0
	la	$a0 int_const1
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label14
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label14:
	lw	$t1	8($a0)
	lw	$t1	40($t1)
	jalr	$t1
# dispatch:cell end
	b	label13
label12:
# dispatch:cell
# push arg :0
	lw	$a0	12($fp)
	sw	$a0	-4($fp)
	la	$a0 int_const0
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
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label15
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label15:
	lw	$t1	8($a0)
	lw	$t1	40($t1)
	jalr	$t1
# dispatch:cell end
label13:
	lw	$fp	28($sp)
	lw	$s0	24($sp)
	lw	$ra	20($sp)
	addiu	$sp	$sp	28
	addiu	$sp	$sp	4
	jr	$ra

CellularAutomaton.cell_at_next_evolution:
	addiu	$sp	$sp	-28
	sw	$fp	28($sp)
	sw	$s0	24($sp)
	sw	$ra	20($sp)
	addiu	$fp	$sp	20
	move	$s0	$a0
# dispatch:cell
# push arg :0
	lw	$a0	12($fp)
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label16
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label16:
	lw	$t1	8($a0)
	lw	$t1	40($t1)
	jalr	$t1
# dispatch:cell end
	sw	$a0	-4($fp)
	la	$a0 str_const2
	sw	$a0	-8($fp)
	la	$a0	bool_const1
	lw	$t1	-4($fp)
	lw	$t2	-8($fp)
	beq	$t1 $t2 label17
	la	$a1	bool_const0
	jal	equality_test
label17:
	lw	$t1	12($a0)
	beqz	$t1 label18
	la	$a0 int_const0
	b	label19
label18:
	la	$a0 int_const1
label19:
	sw	$a0	-4($fp)
# dispatch:cell_left_neighbor
# push arg :0
	lw	$a0	12($fp)
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label20
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label20:
	lw	$t1	8($a0)
	lw	$t1	44($t1)
	jalr	$t1
# dispatch:cell_left_neighbor end
	sw	$a0	-8($fp)
	la	$a0 str_const2
	sw	$a0	-12($fp)
	la	$a0	bool_const1
	lw	$t1	-8($fp)
	lw	$t2	-12($fp)
	beq	$t1 $t2 label21
	la	$a1	bool_const0
	jal	equality_test
label21:
	lw	$t1	12($a0)
	beqz	$t1 label22
	la	$a0 int_const0
	b	label23
label22:
	la	$a0 int_const1
label23:
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
# dispatch:cell_right_neighbor
# push arg :0
	lw	$a0	12($fp)
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label24
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label24:
	lw	$t1	8($a0)
	lw	$t1	48($t1)
	jalr	$t1
# dispatch:cell_right_neighbor end
	sw	$a0	-8($fp)
	la	$a0 str_const2
	sw	$a0	-12($fp)
	la	$a0	bool_const1
	lw	$t1	-8($fp)
	lw	$t2	-12($fp)
	beq	$t1 $t2 label25
	la	$a1	bool_const0
	jal	equality_test
label25:
	lw	$t1	12($a0)
	beqz	$t1 label26
	la	$a0 int_const0
	b	label27
label26:
	la	$a0 int_const1
label27:
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
	la	$a0 int_const0
	sw	$a0	-8($fp)
	la	$a0	bool_const1
	lw	$t1	-4($fp)
	lw	$t2	-8($fp)
	beq	$t1 $t2 label28
	la	$a1	bool_const0
	jal	equality_test
label28:
	lw	$t1	12($a0)
	beqz	$t1 label29
	la	$a0 str_const2
	b	label30
label29:
	la	$a0 str_const3
label30:
	lw	$fp	28($sp)
	lw	$s0	24($sp)
	lw	$ra	20($sp)
	addiu	$sp	$sp	28
	addiu	$sp	$sp	4
	jr	$ra

CellularAutomaton.evolve:
	addiu	$sp	$sp	-32
	sw	$fp	32($sp)
	sw	$s0	28($sp)
	sw	$ra	24($sp)
	addiu	$fp	$sp	24
	move	$s0	$a0
	la	$a0	int_const1
	sw	$a0	-4($fp)
# dispatch:num_cells
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label31
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label31:
	lw	$t1	8($a0)
	lw	$t1	36($t1)
	jalr	$t1
# dispatch:num_cells end
	sw	$a0	-8($fp)
	la	$a0	str_const16
	sw	$a0	-12($fp)
# loop class
label32:
	lw	$a0	-4($fp)
	sw	$a0	-16($fp)
	lw	$a0	-8($fp)
	sw	$a0	-20($fp)
	la	$a0	bool_const1
	lw	$t1	-16($fp)
	lw	$t1	12($t1)
	lw	$t2	-20($fp)
	lw	$t2	12($t2)
	blt	$t1 $t2 label34
	la	$a0	bool_const0
label34:
	lw	$t1	12($a0)
	beqz	$t1 label33
# dispatch:concat
# push arg :0
# dispatch:cell_at_next_evolution
# push arg :0
	lw	$a0	-4($fp)
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# evaluate dispatch expr
	move	$a0	$s0
	bne	$a0 $zero label35
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label35:
	lw	$t1	8($a0)
	lw	$t1	52($t1)
	jalr	$t1
# dispatch:cell_at_next_evolution end
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# evaluate dispatch expr
	lw	$a0	-12($fp)
	bne	$a0 $zero label36
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label36:
	lw	$t1	8($a0)
	lw	$t1	16($t1)
	jalr	$t1
# dispatch:concat end
	sw	$a0	-12($fp)
	lw	$a0	-4($fp)
	sw	$a0	-16($fp)
	la	$a0 int_const0
	sw	$a0	-20($fp)
	la	$a0 Int_protObj
	jal	Object.copy
	jal	Int_init
	lw	$t1	-16($fp)
	lw	$t1	12($t1)
	lw	$t2	-20($fp)
	lw	$t2	12($t2)
	add	$t1	$t1	$t2
	sw	$t1	12($a0)
	sw	$a0	-4($fp)
	b	label32
label33:
	li	$a0 0
# loop class end
	lw	$a0	-12($fp)
	sw	$a0	12($s0)
	move	$a0	$s0
	lw	$fp	32($sp)
	lw	$s0	28($sp)
	lw	$ra	24($sp)
	addiu	$sp	$sp	32
	addiu	$sp	$sp	0
	jr	$ra

Main.main:
	addiu	$sp	$sp	-24
	sw	$fp	24($sp)
	sw	$s0	20($sp)
	sw	$ra	16($sp)
	addiu	$fp	$sp	16
	move	$s0	$a0
# dispatch:init
# push arg :0
	la	$a0 str_const4
	sw	$a0	0($sp)
	addiu	$sp	$sp	-4
# evaluate dispatch expr
	la	$a0 CellularAutomaton_protObj
	jal	Object.copy
	jal	CellularAutomaton_init
	bne	$a0 $zero label37
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label37:
	lw	$t1	8($a0)
	lw	$t1	28($t1)
	jalr	$t1
# dispatch:init end
	sw	$a0	12($s0)
# dispatch:print
# evaluate dispatch expr
	lw	$a0	12($s0)
	bne	$a0 $zero label38
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label38:
	lw	$t1	8($a0)
	lw	$t1	32($t1)
	jalr	$t1
# dispatch:print end
	la	$a0 int_const2
	sw	$a0	-4($fp)
# loop class
label39:
	la	$a0 int_const1
	sw	$a0	-8($fp)
	lw	$a0	-4($fp)
	sw	$a0	-12($fp)
	la	$a0	bool_const1
	lw	$t1	-8($fp)
	lw	$t1	12($t1)
	lw	$t2	-12($fp)
	lw	$t2	12($t2)
	blt	$t1 $t2 label41
	la	$a0	bool_const0
label41:
	lw	$t1	12($a0)
	beqz	$t1 label40
# dispatch:evolve
# evaluate dispatch expr
	lw	$a0	12($s0)
	bne	$a0 $zero label42
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label42:
	lw	$t1	8($a0)
	lw	$t1	56($t1)
	jalr	$t1
# dispatch:evolve end
# dispatch:print
# evaluate dispatch expr
	lw	$a0	12($s0)
	bne	$a0 $zero label43
	la	$a0 str_const0
	li	$t1 1
	jal	_dispatch_abort
label43:
	lw	$t1	8($a0)
	lw	$t1	32($t1)
	jalr	$t1
# dispatch:print end
	lw	$a0	-4($fp)
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
	sub	$t1	$t1	$t2
	sw	$t1	12($a0)
	sw	$a0	-4($fp)
	b	label39
label40:
	li	$a0 0
# loop class end
	move	$a0	$s0
	lw	$fp	24($sp)
	lw	$s0	20($sp)
	lw	$ra	16($sp)
	addiu	$sp	$sp	24
	addiu	$sp	$sp	0
	jr	$ra


# end of generated code

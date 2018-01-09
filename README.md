COOL
----

## Introduction.
COOL is a Classroom Object-Oriented Language developed by Standford.
In this repo, I wrote a compiler for COOL from scratch with reference to 4 PAs I did in the online Standford compiler course.

The Compiler can be divided into 4 parts: lexer, parser, semantic checker and
code generator. I used flex and bison for generating lexer and parser for COOL.
Then Most of my works are focused on writing the semantic checker and code
generator. The final generated code are MIPS assembly and can be run on MIPS
simulator -- SPIM.

The compiler is developed on Mac OS X and compiled with clang.

## Setup 

(1) install spim 

```bash
brea install spim

# overide the excetion.s with trap.handler
cp trap.handler /usr/local/Celler/spim/share/exception.s
```

(2) try

The following 4 bins are independent. We can test different parts of
the compiler.

```bash
# 1. lexer
make cool-lexer

# 2. parser
make cool-parser

# 3. semantic checker
make cool-semant

# 4. code generator
make cool-codegen
```

I also provide 4 scripts for testing the 4 parts with the giving exmaples in
the compiler course. See `test-*.sh` and `*-test-files`

(3) run generated code

```bash
./cool-codegen input-cool.file -o out.s
spim -file out.s
```

## Example of COOL

(1) Dynamic Dispatch

```
class Base inherits IO
{
  identify() : Object
  {
    out_string( "base\n" )
  };
};

class Derived inherits Base
{
  identify() : Object
  {
    out_string( "derived\n" )
  };
};

class Main
{
  main() : Object
  {
    {
      let me : Base <- new Base in me.identify();
      let me : Base <- new Derived in me.identify();
      let me : Derived <- new Derived in
	    me.identify();
    }
  };
};

```

(2) Factorial

```
class Main inherits IO {

  fact(n : Int) : Int {
    if (n = 0)
    then
      1
    else
      n * fact(n - 1)
    fi
  };

  main() : Object { {
    out_int(fact(3));
    out_string("\n");
  } };
};
```

## TODO
1. Read and rewrite the trap handler for COOL runtime.
2. Try optimize generate code.
3. Try change language syntax.

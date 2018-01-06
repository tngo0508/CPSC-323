# CPSC-323
compiler


                                               ### Project for CPSC323
                                                                    Fall 2017
The programming assignments are based on a language called "Rat17F" which is described as
follows. The Rat17F language is designed to be easy to understand. It has a short grammar and  relatively clean semantics. 


                                                                 RAT17F
1) Lexical Conventions:
The lexical units of a program are identifiers, keywords, integers, reals, operators and other 
separators. Blanks, tabs and newlines  (collectively, "white space") as described below
are ignored except as they serve to separate tokens.
Some white space is required to separate otherwise adjacent identifiers, keywords, reals and integers.
<Identifier> is a sequence of letters and   “#”. 
The first character must be a letter and two consecutive #s are not allowed.
Upper and lower cases are same.
<Integer>  is an unsigned decimal integer i.e., a sequence of decimal digits.
<floating> is integer followed by “.”and integer, e.g., 123.00
Some identifiers are reserved for use as keywords, and may not be used otherwise:
       e.g.,  int, if, else, fi,  while, return, read, write  etc


2) Syntax rules 

The following BNF  describes the  Rat17F.  
<Rat17F>  ::=  <Opt Function Definitions>  
                         %%  <Opt Declaration List> <Statement List>    
<Opt Function Definitions> ::= <Function Definitions> | <Empty>
<Function Definitions>  ::= <Function> | <Function> <Function Definitions>   
<Function> ::=  @  <Identifier>  (<Opt Parameter List> )   <Opt Declaration List>  <Body>
<Opt Parameter List> ::=  <Parameter List>   |  <Empty>
<Parameter List>  ::=  <Parameter>  | <Parameter> , <Parameter List>
<Parameter> ::=  <IDs > : <Qualifier> 
<Qualifier> ::= integer   |  boolean  |  floating
<Body>  ::=  {  < Statement List>  }
<Opt Declaration List> ::= <Declaration List>   | <Empty>
<Declaration List>  := <Declaration> ;  | <Declaration> ; <Declaration List>
<Declaration> ::=  <Qualifier > <IDs>                   
<IDs> ::=  <Identifier>    | <Identifier>, <IDs>
<Statement List> ::=  <Statement>   | <Statement> <Statement List>
<Statement> ::=  <Compound> | <Assign> | <If> |  <Return> | <Write> | <Read> | <While> 
<Compound> ::= {  <Statement List>  } 
<Assign> ::=   <Identifier> := <Expression> ;
<If> ::=     if  ( <Condition>  ) <Statement> fi    |   
                  if  ( <Condition>  ) <Statement>   else <Statement> fi   
<Return> ::=  return ; |  return <Expression> ;
<Write> ::=   write ( <Expression>);
<Read> ::=    read ( <IDs> );
<While> ::= while ( <Condition>  )  <Statement> 
<Condition> ::= <Expression>  <Relop>   <Expression>
<Relop> ::=   = |  /=  |   >   | <   |  =>   | <=            
<Expression>  ::= <Expression> + <Term>  | <Expression>  - <Term>  | <Term>
<Term>    ::=  <Term> * <Factor>  | <Term> / <Factor> |  <Factor>
<Factor> ::= - <Primary>   | <Primary>
<Primary> ::= <Identifier> | <Integer> | <Identifier> [<IDs>]  | 
                       ( <Expression> ) |  <Real>  | true | false                        
<Empty>   ::= 


3) Some Semantics
	Rat17F is a conventional imperative programming language. A Rat17F program consists of a sequence of functions followed  by the "main body"  where the program executes. 
	All variables and functions must be declared before use.
	Function arguments are passed by value. 
	There is an implied expressionless return at the end of all functions; the value returned by  expressionless return statement is undefined. 
	Arithmetic expressions have their conventional meanings. 
	Integer division ignores any remainder. 
	Type casting is not allowed (e.g., assigning an integer to a real variable)
	No arithmetic operations are allowed with booleans (e.g., true + false)
	Others as we will define during the semester 


4)  A sample Rat17F Program 


@ convert  (fahr : integer)
{
           return 5*(fahr -32)/9;
}

%%
     integer   low, high, step#xy;

     read(low, high, step#xy );
     while (low < high)  
         {  write  (low);
             write (convert [low]);
             low := low + step#xy;
         } 











                                                   VERY, VERY  IMPORTANT !!!

                    For each programming assignment,  you should turn in the following:

1)	A hardcopy of 
   a) Cover page with name(s) – provided
   b) 2-3 pages of Assignment Documentation - provided
   c) Source code listing with proper comments for each procedures, sections if 
        necessary.
   d) Your Test cases.  Find at least 3 test cases  (< 10,   < 20,    > 20  lines)  
   e)  Results of the testing

2)	You will also have to submit a softcopy of all mentioned in (1) and executable file e.g., (.exe) under DOS/WINDOW using the “submit” feature on Tatanium.
Before submission, Zip your files and submit the “zipped” files.

Note:  1.  I must be able to run your program in order to give you a grade.
            2. I will accept late project however, there will be some deductions:
                2 points deduction for the first day and 0.1 each day you are late 
                (from max of 10). For example,  if you are late for one week, then the 
                 maximum point you will get  is 10 – ( 2 + .6 ) = 7.4
            3. If you turn in a program that cannot be run, there will be an automatic 2 points
                deduction.
            4. If you don’t turn in the documentation, there will be an automatic 2 points 
                deduction.

Final Notes:    -    You will most likely not pass this course without doing the projects
-	The projects are built on each other, so make sure that you do well the
       first project


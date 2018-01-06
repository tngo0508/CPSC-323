# CPSC-323
compiler
                                                                  
### Fall 2017
The programming assignments are based on a language called "Rat17F" which is described as follows. The Rat17F language is designed to be easy to understand. It has a short grammar and  relatively clean semantics. <br>

### RAT17F
1) Lexical Conventions: <br>
```
The lexical units of a program are identifiers, keywords, integers, reals, operators and other separators. 
Blanks, tabs and newlines  (collectively, "white space") as described below are ignored except 
as they serve to separate tokens. 
Some white space is required to separate otherwise adjacent identifiers, keywords, reals and integers.
<Identifier> is a sequence of letters and   “#”. 
The first character must be a letter and two consecutive #s are not allowed. 
Upper and lower cases are same. 
<Integer>  is an unsigned decimal integer i.e., a sequence of decimal digits.
<floating> is integer followed by “.”and integer, e.g., 123.00 
Some identifiers are reserved for use as keywords, and may not be used otherwise:
       e.g.,  int, if, else, fi,  while, return, read, write  etc
```
2) Syntax rules <br>
```
The following BNF  describes the  Rat17F.   
<Rat17F>  ::=  <Opt Function Definitions> 
                         %%  <Opt Declaration List> <Statement List>    
<Opt Function Definitions> ::= <Function Definitions> | <Empty> 
<Function Definitions>  ::= <Function> | <Function> <Function Definitions>   
<Function> ::=  @  <Identifier>  (<Opt Parameter List> )   <Opt Declaration List>  <Body> 
<Opt Parameter List> ::=  <Parameter List>   |  <Empty> <
<Parameter List>  ::=  <Parameter>  | <Parameter> , <Parameter List> 
<Parameter> ::=  <IDs > : <Qualifier> <br>
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
<Empty>   ::= epsilon 
```

3) Some Semantics <br>
+	Rat17F is a conventional imperative programming language. A Rat17F program consists of a sequence of functions followed  by the "main body"  where the program executes.  
+	All variables and functions must be declared before use.
+	Function arguments are passed by value. 
+	There is an implied expressionless return at the end of all functions; the value returned by  expressionless return statement is undefined. 
+	Arithmetic expressions have their conventional meanings. 
+	Integer division ignores any remainder. 
+	Type casting is not allowed (e.g., assigning an integer to a real variable)
+	No arithmetic operations are allowed with booleans (e.g., true + false)
+	Others as we will define during the semester 


4)  A sample Rat17F Program <br>

```
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
```

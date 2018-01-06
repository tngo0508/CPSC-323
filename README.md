# CPSC-323
compiler
                                                                  
### Fall 2017
The programming assignments are based on a language called "Rat17F" which is described as follows. The Rat17F language is designed to be easy to understand. It has a short grammar and  relatively clean semantics. <br>

### RAT17F
1) Lexical Conventions: <br>
The lexical units of a program are identifiers, keywords, integers, reals, operators and other separators. Blanks, tabs and newlines  (collectively, "white space") as described below are ignored except as they serve to separate tokens. <br>
Some white space is required to separate otherwise adjacent identifiers, keywords, reals and integers. <br>
<Identifier> is a sequence of letters and   “#”. <br>
The first character must be a letter and two consecutive #s are not allowed. <br>
Upper and lower cases are same. <br>
<Integer>  is an unsigned decimal integer i.e., a sequence of decimal digits. <br>
<floating> is integer followed by “.”and integer, e.g., 123.00 <br>
Some identifiers are reserved for use as keywords, and may not be used otherwise: <br>
       e.g.,  int, if, else, fi,  while, return, read, write  etc <br>

2) Syntax rules <br>
```
The following BNF  describes the  Rat17F. <br>  
<Rat17F>  ::=  <Opt Function Definitions> 
                         %%  <Opt Declaration List> <Statement List>    <br>
<Opt Function Definitions> ::= <Function Definitions> | <Empty> <br>
<Function Definitions>  ::= <Function> | <Function> <Function Definitions> <br>  
<Function> ::=  @  <Identifier>  (<Opt Parameter List> )   <Opt Declaration List>  <Body> <br>
<Opt Parameter List> ::=  <Parameter List>   |  <Empty> <br>
<Parameter List>  ::=  <Parameter>  | <Parameter> , <Parameter List> <br>
<Parameter> ::=  <IDs > : <Qualifier> <br>
<Qualifier> ::= integer   |  boolean  |  floating <br>
<Body>  ::=  {  < Statement List>  } <br>
<Opt Declaration List> ::= <Declaration List>   | <Empty> <br>
<Declaration List>  := <Declaration> ;  | <Declaration> ; <Declaration List> <br>
<Declaration> ::=  <Qualifier > <IDs>      <br>              
<IDs> ::=  <Identifier>    | <Identifier>, <IDs> <br>
<Statement List> ::=  <Statement>   | <Statement> <Statement List> <br>
<Statement> ::=  <Compound> | <Assign> | <If> |  <Return> | <Write> | <Read> | <While>  <br>
<Compound> ::= {  <Statement List>  } <br>
<Assign> ::=   <Identifier> := <Expression> ; <br>
<If> ::=     if  ( <Condition>  ) <Statement> fi    |   
                  if  ( <Condition>  ) <Statement>   else <Statement> fi   <br>
<Return> ::=  return ; |  return <Expression> ; <br>
<Write> ::=   write ( <Expression>); <br>
<Read> ::=    read ( <IDs> ); <br>
<While> ::= while ( <Condition>  )  <Statement> <br>
<Condition> ::= <Expression>  <Relop>   <Expression> <br>
<Relop> ::=   = |  /=  |   >   | <   |  =>   | <=            <br>
<Expression>  ::= <Expression> + <Term>  | <Expression>  - <Term>  | <Term> <br>
<Term>    ::=  <Term> * <Factor>  | <Term> / <Factor> |  <Factor> <br>
<Factor> ::= - <Primary>   | <Primary> <br>
<Primary> ::= <Identifier> | <Integer> | <Identifier> [<IDs>]  | 
                       ( <Expression> ) |  <Real>  | true | false    <br>                    
<Empty>   ::= epsilon <br>
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

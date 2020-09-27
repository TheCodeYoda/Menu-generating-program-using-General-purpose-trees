# Menu-generating-program-using-General-purpose-trees

HELPER FUNCTIONS:
--------------------------------------------------------------------------------------------
1)Input_string(..) which helps to take any variable length input string
2)remove_Tabs() This function basically trims all tabs from the taken Input

Code Generating functions:
---------------------------------------------------------------------------------------------
1)gen_while() generates a while loop (opens a while loop)
2)gen_while_withoutopt() generates a while loop whithout redeclaring a variable called "opt".
3)close_while() closes the generated while loop
4)gen_fn(..) generates a function with function name as given string This is a utility function to print given node content.
5)gen_break() generates a break statement.
6)gen_case() generates a case statement.
7)gen_header() basically includes all header files required
8)gen_prolog() opens "int main".
9)gen_epilog() closes "int main".

Note: All these functions are implemented as discussed in the class

Tree generation:
----------------------------------------------------------------------------------------------
The tree structure is defined like this it has an element of node_t type called root.Further node_t is defined like this it has 2 pointers node_t *left , node_t *right and char *key.As discussed in the class left pointer holds "children" and the right pointer holds "siblings".

Steps to generate the GPT:

1)First we call init_tree() to initialise the root of the tree.

2)We process the input line by line till we reach EOF.As we process the input I have created an elementary data structure in this case a stack(array form), The purpose of this is to basically to mantain the parent of the next coming input.This is how it works initially the parent is initialised " " as we enter 1 level inside(as 1 tab count increase) we initialise the parent to stack[top] and push the node into the stack. but if we come out k levels (i.e come back k tab spaces) we pop k elements from the stack and then initialise parent to stack[top](edge cases like when the stack is empty is handled accordingly), now the third case which can occur if we are on the same indentation level we pop 1 element and push that respective node,This ensures that if we are on the same level as previous the parent will not be the one on the previous level but will be updated due to the pop-push operation.

I have push(..), pop(..) functions to perform push and pop operations.

3)Now as we can get the parent of the incoming input from the stack we then call add_node(tree,parent,child) to add the node into the tree, This works like this if the parent is " ",then it indicates its a root or sibling of root so we only traverse the right pointer line go to the end and attach the node.Second case if it is some internal node having a parent Then we search for the parent in the tree using a recursive search function "node_t *search(...)" which returns the address of the parent,then we check if the left pointer is free if it is free we attach the child there and if its not free we traverse left once and then right (sibling as it children are in the same level) until we reach the last node in that line finally attaching the child here.

Tree is created!!!

Menu Creation By Tree Traversal:
-----------------------------------------------------------------------------------------------------
The main fxn is disp_tree(..) which then calls helper functions to generate the menu.

In disp_tree(..) we first call disp_r_fxn(..) which does a dfs traversal on the tree generating functions to print contents of all nodes.Ex: if we have 3 nodes AA,BB,CC we create fxn_AA() which prints "AA" same for the other two.

Now as the functions are ready in disp_tree we call header,prologue,gen_while()[to open the first while] Then we call another utility function called "disp_r_dfs(node,count)" This function is again a dfs traversal but it also generates code , we have a parameter called count which mantains the "case" number, so here's how it works as we enter the dfs call we generate case for that particular node then we check if it has a non null left node if it has we call gen_whilewithoutopt() and  dfs(on left child,1) with count as 1 as it is increasing one level everytime (nesting level is increased by 1).Then as the recursive calls return we generate break and close while accordingly.

After this we check if we have a non null right node we call dfs(node,count+1) by incrementing count number as right node represents "sibling" so we are in the same level so case number should increase by one as siblings are encountered.Then we generate break statements accordingly.

Lastly we close while() for the first one opened in disp_tree(..) also generate a break for the last case then we call epilog() and end the program.

So now when we run the program a menu driven program will be generated.
-----------------------------------------------------------------------------------------------------

POINTS to be NOTED:

1) The stack size is 1500 as we know that max characters in a line is 1024 this means that it can be max 1023 tabs and 1 character , so max depth of tree is 1024 therefore the size of stack is also equivalent to the depth of the tree.
 

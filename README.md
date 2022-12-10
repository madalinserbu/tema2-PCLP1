Serbu Ovidiu-Madalin, 324CA

## Task 1

-> In the first task we dynamically allocate space for a matrix using allocate_data function. After that, we read the elements of the new matrix into an array of matrices. That array is reallocated before each sted, making space for the new element. We also create an array of structures meant to store each matrices' size (number of rows and columns)
-> One important thing to note is that the function returns the address of the 3d-array in order for it to properly be reallocated; same thing goes for the array of structs, modified by accesing their address.
-> In main we declare a variable for every command we have to implement, a variable for the collection of matrices (the triple pointer), one that counts the number of stored matrices and the array of structures. The 2 arrays are initialized with space for only one element.
-------------------------------------------------------------------------------

## Task2

-> The main type of data used for this task is the array of structures mentioned before (the dimensions of each matrix are contained in it)
-> The index is read, and processed accordingly:
    -> either printing the error message, when the matrix doesn't exist
    -> or the said number of lines and columns
-------------------------------------------------------------------------------

## Task 3

-> In this task we print the matrix with a given index starting with checking whether the index is valid (if the matrix exists) and reading the matrix using the 3d-array because the matrix isn't stored elsewhere.
-------------------------------------------------------------------------------

## Task 4

-> We read the input first: the index, the number of lines, their indexes, the number of columns and their indexes, all refering to the new matrix
-> We store the number of rows and the number of columns in two arrays, dynamically allocated
-> Create the new matrix afterwards:
    -> for every line index, we associate every column index, moving into the new matrix the value stored in the old one at the said indexes
    -> after this, the old matrix must be freed
-> The next step is to insert the croped matrix back into our collection and update its dimensions
-> Last but not least, the arrays used for storing the lines and columns for the cropped matrix must be freed
-------------------------------------------------------------------------------

## Task 5

-> After considering the error inducing cases, we move on to the multiplication algorithm:
    -> 1st step: allocating memory for a the result of  the multiplication
    -> 2nd step: implementing the multiplication, at the beginning setting the result to 0
    -> 3rd step: reallocating memory for the new matrix (on the array of matrices as well as on the array of dimensions)
    -> 4th step: inserting the matrix at the back of our collection
-------------------------------------------------------------------------------

## Task 6

-> For this task we used multiple helper functions: one that calculates the sum of each matrix, one that swaps elements during sorting and one that does the sorting 
-> We allocate space for the said array of sums
-> We calculate the sum for each matrix % MOD, to avoid overflow
-> Lastly, the pointer to the first element of the array is returned
-> The sorting algorithm is a simple bubble sort applied to the sum array:
    -> we shouldn't forget when swapping to work on the other arrays too, the triple pointer and the dimension struct
-> Fianlly we free the array of sums
-------------------------------------------------------------------------------

## Task 7

-> The main goal of this task is to create yet another new matrix in which the transpose will be constructed
-> Obviously, the transpose will also be allocated dynamically
-> The transposing algorithm is based on the mathematical observation that however we'll choose `t[i][j]`, an element of the transpose, its corespondent from the original (let it be a) is `a[j][i]`
-> Getting rid of the old matrix is a must, so we'll free it
-> The transpose takes its place in the array of the matrices
-> The dimensions are updated, by swapping the number of rows with the number of columns
-------------------------------------------------------------------------------

## Task 8

-> Freeing data for a single matrix is handled by quite literally freeing the space it uses
-> We'll subsequently copy all the matrices after this particular one, one index to the left, in order to not leave unused gaps in our array
-> At the same time, we'll apply the same modifications to the array of structures
-> Reallocating memory is only necessary when we have more than one element left in our arrays, justified by the fact that allocating space for an array of 0 elements doesn't make sense
-> Returning the array of matrices, so the modifications are visible in main
-------------------------------------------------------------------------------

## Task 9

-> The last function gets rid of all the allocated space and helps keeping an optimal usage of resources
-> Deallocating the matrices first
-> Deallocating the array by itself
-> We don't forget about the array of structures
-------------------------------------------------------------------------------

## Task 10

-> This implementation is based on the mathematical observation that we can partition every matrix into 4 differrent blocks and perform on them the multiplication algorithm based on a divide and conquer approach
-> However, to avoid still making 8 multiplications for every step, the aforementioned partitions are used to implement only 7 multiplications, as it goes:
    -> Let a11, a12, a21, a22 be the blocks derived from the first matrix
    -> And b11, b12, b21, b22 the blocks derived from the second matrix
    -> Using them we define 7 new matrices which are going to provide the final result of the multiplication
    -> p1 = (a11 + a22)*(b11 + b22)

      p2 = (a21 + a22)*b11

      p3 = a11*(b12 - b22)

      p4 = a22*(b21 - b11)

      p5 = (a11 + a12)*b22

      p6 = (a21 - a11)*(b11 + b12)

      p7 = (a12 - a22)*(b21 + b22)
    -> Let c be the result:

      c11 = p1 + p4 - p5 + p7

      c12 = p3 + p5

      c21 = p2 + p4
      
      c22 = p1 - p2 + p3 + p6
    -> Because of their definition, an eight multiplication isn't necessary, thus optimizing the time complexity
    -> We reiterate the same partitions until the matrices are made of only one element
    -> At the same time we calculate the result, by integrating the blocks back into the matrix that stores the multiplication
    -> The last step is to deallocate the space used for the matrix zones
    
    
That being said, I find this homework very helpful for understanding the concepts of dynamic allocation and working my way into studying C language.
